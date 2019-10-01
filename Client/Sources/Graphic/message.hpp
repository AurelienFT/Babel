#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QList>
#include "customwidget.hpp"

namespace Babel {

    namespace Graphic {

        class message {

            public:
                message(QString sender, QString message, QPair<qint32, qint32> s_size, QPair<qint32, qint32> m_size);
                customWidget *getWidgetSender();
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
