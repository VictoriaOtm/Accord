#include "message.h"
#include <iostream>

namespace Player{
    
    //извлечение всей информации из указателя на GstMessage
    Message::Message(GstMessage *msg){
        if(msg == NULL) return;
        source = std::string(GST_MESSAGE_SRC_NAME(msg)); //получаем назваие элемента-источника
        GError *err;
        char *debug;

        std::string oldStateStr;
        std::string newStateStr;

        switch(GST_MESSAGE_TYPE(msg)){
            case GST_MESSAGE_INFO:
                type = INFO;
                gst_message_parse_info(msg, &err, &debug); // парсим сообщение как инфо
                msgText = std::string(err->message);
                debugString = std::string(debug);
                g_error_free(err);
                g_free(debug);
                break;
            case GST_MESSAGE_WARNING:
                type = WARNING;
                gst_message_parse_warning(msg, &err, &debug); // парсим сообщение как warning
                msgText = std::string(err->message);
                debugString = std::string(debug);
                g_error_free(err);
                g_free(debug);
                break;
            case GST_MESSAGE_ERROR:
                type = ERROR;
                gst_message_parse_error(msg, &err, &debug); //парсим как ошибку
                msgText = std::string(err->message);
                debugString = std::string(debug);
                g_error_free(err);
                g_free(debug);
                break;
            case GST_MESSAGE_STATE_CHANGED: 
                type = STATE_CHANGED;
                GstState oldState, newState;
                gst_message_parse_state_changed(msg, &oldState, &newState, NULL); //парсим как изменение состояния
                oldStateStr = std::string(gst_element_state_get_name(oldState)); //получаем имена старого и нового состояния
                newStateStr = std::string(gst_element_state_get_name(newState));
                msgText = "State changed: " + oldStateStr + "->" + newStateStr;
                break;
            default:
                type = UNDEFINED;
                break;
        }
    }

    std::string Message::GetMessageText(){
        return msgText;
    }

    MessageType Message::GetType(){
        return type;
    }
    
    std::string Message::GetDebugString(){
        return debugString;
    }

    std::string Message::GetSourceName(){
        return source;
    }

}