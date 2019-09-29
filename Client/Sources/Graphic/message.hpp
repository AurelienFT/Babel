#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QList>
#include "customwidget.hpp"


class message
{
public:
    message(QString sender, QString message, QPair<qint32, qint32> s_size, QPair<qint32, qint32> m_size);
    customWidget *getWidgetSender();
    customWidget *getWidgetMessage();

private:
    QString m_sender;
    QString m_message;
    customWidget *m_widget_message;
    customWidget *m_widget_sender;
};

#endif // MESSAGE_H
