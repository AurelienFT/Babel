#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QList>
#include "customwidget.hpp"

namespace Babel {

    namespace Graphic {

        class message {

            public:
            /**
                *constructor : build a message object
            */
                message(QString sender, QString message, QPair<qint32, qint32> s_size, QPair<qint32, qint32> m_size);
            /**
                *destructor : destroy a message object
            */
                ~message() = default;
            /**
                *get a customWidget
                @return _widgetSender
            */
                customWidget *getWidgetSender();
            /**
                *get a customWidget 
                @return _widgetMessage
            */
                customWidget *getWidgetMessage();

            private:
                QString _messageSender;
                QString _messageTxt;
                customWidget *_widgetMessage;
                customWidget *_widgetSender;
        };
    }
}

#endif // MESSAGE_H
