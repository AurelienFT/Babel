#include "contact.h"

contact::contact(QString name, qint32 index) : c_name(name), c_index(index)
{
    QList<qint32> color = {47, 49, 54, 255};
    QPair<qint32, qint32> size(280, 50);
    QPair<qint32, qint32> pos(0, 1);

    c_widget = new customWidget(color, size, pos, c_name, nullptr);
}

customWidget *contact::getContactWidget(void)
{
    return (c_widget);
}


