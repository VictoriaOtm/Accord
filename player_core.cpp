#include "player_core.h"
#include <thread>

static void (*EosCallback) ();
static void (*MessageCallback) (Player::Message message);

static GstElement *pipeline; //конвейер. Глобальный, так как должен быть доступен потоку

enum State{
    INIT,  //в таком статусе Player находится только после инициализации, когда поток воспроизведения не запущен
            //означает, что при вызове StartPlayback нужно запустить новый поток
    PLAYING, //Player проигрывает аудио, конвейер находится в состоянии GST_STATE_PLAYING
    TO_PAUSE, //Player на следующей итерации цикла должен перевести себя в состояние PAUSED
    PAUSED, //конвейер переведён в состояние GST_STATE_PAUSED
    TO_RESUME, //Player на следующей итерации цикла должен перевести себя в состояние PLAYING
    TO_STOP, //Player должен выйти из цикла проигрывания досрочно, чтобы был возможен join потока
    EOS //Конец файла. Player снова можно запустить функцией StartPlayback
};

static State state;

static std::thread playbackThread;

//ОБРАБОТЧИК СОБЫТИЯ ДОБАВЛЕНИЯ НОВОГО ВЫХОДА У ДЕКОДЕРА
static void NewPadCallback(GstElement *element, GstPad *pad, gpointer data){
    //element - указатель на декодер, событие которого случилось
    //pad - новый созданный выход
    //по указателю data лежит указатель на конвертер, переданный как аргумент при прикреплении обработчика к событию
    gchar *name = gst_pad_get_name(pad); //получаем имя нового выхода
    gst_element_link_pads(element, name, GST_ELEMENT(data), "sink"); //связываем выход и вход по именам
    //sink - название входа конвертера
    //GST_ELEMENT(data) - cast к типу GST_ELEMENT
    g_free(name);
}

//ПОТОК ПРОИГРЫВАНИЯ
static void PlaybackThread(void (*MsgCB)(Player::Message m), void (*EosCB)(void)){
    //при старте потока переводим конвейер в состояние PLAYING
    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);

    //получаем указатель на шину сообщений конвейера
    GstBus *bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    GstMessage *msg = NULL;

    //пока никакого сообщения не получено или полученное сообщение не извещает о конце файла
    while(msg == NULL || GST_MESSAGE_TYPE(msg) != GST_MESSAGE_EOS){
        //достаём последнее сообщение с шины
        msg = gst_bus_pop(bus);
        
        if(msg != NULL){
            Player::Message message(msg);
            //вызываем callback обработки сообщения
            MsgCB(message);
            //выбрасываем ссылку на msg (это ебанутое ООП на Си - то, что C++ делает автоматически)
            gst_message_unref(msg);
        }

        if(state == TO_PAUSE){ //если на этой итерации нужно приостановить проигрывание
            gst_element_set_state(pipeline, GST_STATE_PAUSED); //ставим конвейер на паузу
            state = PAUSED; //устанавливаем своё состояние на паузу
        }else if(state == TO_RESUME){ //если на этой итерации нужно возобновить
            gst_element_set_state(pipeline, GST_STATE_PLAYING); //возобновляем
            state = PLAYING;
        }else if(state == TO_STOP){ //если нужно остановить проигрывание, выходим из цикла
            break;
        }
    }

    //если вышли из цикла, то либо достигли конца файла, либо досрочно остановили проигрывание
    //досрочная остановка - это не вызов PlaybackStop!!!
    //это вызов Dispose, в котором поток нельзя остановить, пока цикл не кончится
    //т.е., TO_STOP нужен для выхода из цикла

    
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    state = EOS;
    EosCB();
}

namespace Player{
    void Init(void (*EosCB)(), void (*MessageCB)(Message message), std::string path){
        //ссылки на элементы - источник (файл), декодер, конвертер аудио, приемник
        GstElement *source, *decode, *convert, *sink;

        //установка callback-ов
        EosCallback = EosCB;
        MessageCallback = MessageCB;
        
        //создаём новый конвейер
        pipeline = gst_pipeline_new("my-pipeline");
        source = gst_element_factory_make("filesrc", "file-source"); //создаем элемент filesrc
        decode = gst_element_factory_make("decodebin", "decode"); //создаем автоматический декодер
        convert = gst_element_factory_make("audioconvert", "audio-convert"); //создаём конвертер
        sink = gst_element_factory_make("autoaudiosink", "output-sink"); //создаём автоматический приемник
        //автоприемник выбирает способ вывода звука автоматически
    
        g_object_set(source, "location", path.c_str(), NULL); //установка у элемента filesrc параметра 
                                                            //location - путь к файлу

        gst_bin_add_many(GST_BIN(pipeline), source, decode, convert, sink, NULL);
                                    //установка элементов в конвейер
        
        gst_element_link(source, decode); //связываем выход источника со входом декодера
        gst_element_link(convert, sink); //связываем выход конвертера со входом приемника
        /*декодер не связывается с конвертером, потому что выход декодера динамический,
          т.е. создаётся только тогда, когда декодер готов к обработке файла
        */
        g_signal_connect(decode, "pad-added", G_CALLBACK(NewPadCallback), convert);
        /* Поэтому вешаем на событие pad-added декодера callback NewPadCallback, а как параметр передаем
           указатель на конвертер, к которому должен быть присоединен выход декодера (pad - "разъём")
        */

        gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PAUSED); //установка статуса конвейера на паузу
        state = INIT;  //Подробнее о значении статусов выше
    }

    void StartPlayback(){
        if(state == EOS){
            playbackThread.join(); //присоединяем законченный поток
        }
        if(state == INIT || state == EOS){
            //если мы или в самом начале, или когда поток уже остановлен
            //запускаем поток
            playbackThread = std::thread(PlaybackThread, MessageCallback, EosCallback);
        }
        //иначе нужно просто возобновить вопроизведение в потоке
        state = TO_RESUME;
    }
    void PausePlayback(){
        if(state == PLAYING) //проигрывание можно остановить только во время проигрывания (очевидно, не правда ли?)
            state = TO_PAUSE;
    }
    void StopPlayback(){
        if(state != EOS){
            gst_element_set_state(pipeline, GST_STATE_READY); //"перезагружаем" конвейер
            gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PAUSED);
            state = PAUSED;
        }
    }
    void Dispose(){
        state = TO_STOP; //переводим в это состояние для выхода из цикла потока
        playbackThread.join(); //присоединяем поток
        gst_element_set_state(pipeline, GST_STATE_NULL); //переводя в это состояние, очищаем все буферы
        gst_object_unref(GST_OBJECT(pipeline)); //избавляемся от ссылки на конвейер
    }
};