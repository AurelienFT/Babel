#include "message.hpp"

Babel::Graphic::message::message(QString sender, QString message, QPair<qint32, qint32> s_size, QPair<qint32, qint32> m_size) : _messageSender(sender), _messageTxt(message)
{
    QList<qint32> m_color = {54, 57, 63, 255};
    QList<qint32> s_color = {32, 34, 37, 255};
    QPair<qint32, qint32> pos(0, 0);

    _widgetSender = new Babel::Graphic::customWidget(s_color, s_size, pos, _messageSender, nullptr);
    _widgetMessage = new Babel::Graphic::customWidget(m_color, m_size, pos, _messageTxt, nullptr);

}

Babel::Graphic::customWidget *Babel::Graphic::message::getWidgetSender()
{
    return (_widgetSender);
}

Babel::Graphic::customWidget *Babel::Graphic::message::getWidgetMessage()
{
    return (_widgetMessage);
}


