#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QList>
#include <customwidget.h>


class message
{
public:
    message(QString sender, QString message);
    customWidget *getWidgetSender();
    customWidget *getWidgetMessage();

private:
    QString m_sender;
    QString m_message;
    customWidget *m_widget_message;
    customWidget *m_widget_sender;
};

#endif // MESSAGE_H
