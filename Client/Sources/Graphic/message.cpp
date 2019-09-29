#include "message.hpp"

message::message(QString sender, QString message, QPair<qint32, qint32> s_size, QPair<qint32, qint32> m_size) : m_sender(sender), m_message(message)
{
    QList<qint32> m_color = {54, 57, 63, 255};
    QList<qint32> s_color = {32, 34, 37, 255};
    QPair<qint32, qint32> pos(0, 0);

    m_widget_sender = new customWidget(s_color, s_size, pos, m_sender, nullptr);
    m_widget_message = new customWidget(m_color, m_size, pos, m_message, nullptr);

}

customWidget *message::getWidgetSender()
{
    return (m_widget_sender);
}

customWidget *message::getWidgetMessage()
{
    return (m_widget_message);
}


