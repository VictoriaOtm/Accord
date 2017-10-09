#ifndef __PLAYER_CORE_H__
#define __PLAYER_CORE_H__

/**
 * ИСПОЛЬЗОВАНИЕ
 * 1. Необходим установленный gstreamer. 
 *    Установка: https://gstreamer.freedesktop.org/documentation/installing/on-linux.html
 * 2. Подключаем player_core.h и message.h для обработки сообщений от проигрывателя
 * 3. Реализуем callback-функции MessageCallback(Message) и EosCallback() - callback конца файла. 
 *    О Message подробнее в message.h
 * 4. На старте int main(int argc, char *argv[]) необходимо вызвать gst_init(&argc, &argv) - инициализация
 *    gstreamer-а
 * 5. Для установки пути к дорожке и callback-функций вызываем Player::Init(EosCB, MsgCB, string path)
 * 6. В этот момент Player готов начать проигрывание дорожки
 * 7. StartPlayback - запуск потока и начало проигрывания. PausePlayback - пауза. Возобновление - 
 *    повторный вызов StartPlayback. Возврат в начало песни - StopPlayback. Чтобы снова начать 
 *    воспроизведение, вызови StartPlayback.
 * 8. При необходимости сменить дорожку, вызываем Dispose (остановка потока, очистка всех буферов и данных),
 *    а затем снова начиная с пункта 5.
 * 9. В EosCallback() вызови Player::StopPlayback(), чтобы снова привести проигрыватель в состояние готовности
 * 
 * Пример реализации MessageCallback:
 * 
 * void MessageCallback(Message m){
     std::cout << "Message: " << m.GetMessageText() << std::endl;
     switch(m.GetType()){
        case INFO:
            std::cout << "Type: info" << std::endl;
            std::cout << "Debug info: " << m.GetDebugString() << std::endl;
            break;
        case WARNING:
            std::cout << "Type: warning" << std::endl;
            std::cout << "Debug info: " << m.GetDebugString() << std::endl;
            break;
        case ERROR:
            std::cout << "Type: error" << std::endl;
            std::cout << "Debug info: " << m.GetDebugString() << std::endl;
            break;
        case STATE_CHANGED:
            std::cout << "Type: state_changed" << std::endl;
            break;
        case UNDEFINED:
            std::cout << "Type: undefined" << std::endl;
            break;
     }
}
 * */

#include <iostream>
#include <gst/gst.h>
#include <string>
#include "message.h"

namespace Player{
    void Init(void (*EosCallback)(void), void (*MessageCallback)(Message message), std::string path);
    void StartPlayback();
    void PausePlayback();
    void StopPlayback();
    void Dispose();
};

#endif