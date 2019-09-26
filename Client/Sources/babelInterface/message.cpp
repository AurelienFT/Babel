#include "message.h"

message::message(QString sender, QString message) : m_sender(sender), m_message(message)
{
    QList<qint32> color = {32, 34, 60, 255};
    QPair<qint32, qint32> size(1620, 100);
    QPair<qint32, qint32> pos(0, 0);

    m_widget_sender = new customWidget(color, size, pos, m_sender, nullptr);
    m_widget_message = new customWidget(color, size, pos, m_message, nullptr);

}

customWidget *message::getWidgetSender()
{
    return (m_widget_sender);
}

customWidget *message::getWidgetMessage()
{
    return (m_widget_message);
}


