#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <gst/gst.h>
#include <string>

namespace Player{
    /**
     * Разные элементы посылают сообщения на шину конвейера.
     * Сейчас нас, наверно, интересует только следующее:
     * тип: ERROR
     * msgText: "Resource not found."
     * В принципе, все сообщения можно перехватывать и печатать на консоль. Для этого мы пишем callback
     * О callback-е в player_core.h
     * */

    enum MessageType{
        INFO, //просто информация, ничего серьёзного
        WARNING, //ошибка, которая не останавливает конвейер
        ERROR, //фатальная ошибка, остановка конвейера
        UNDEFINED, //нипанятна
        STATE_CHANGED //элемент изменил состояне
    };

    class Message{
        public:
            explicit Message(GstMessage *msg);
            std::string GetSourceName();
            MessageType GetType();
            std::string GetMessageText();
            std::string GetDebugString();
            ~Message() = default;
        private:
            std::string source;
            MessageType type;
            std::string msgText;
            std::string debugString;
    };
};

#endif

