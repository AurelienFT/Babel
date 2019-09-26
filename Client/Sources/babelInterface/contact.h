#ifndef CONTACT_H
#define CONTACT_H

#include "customwidget.h"

class contact
{

public:

    contact(QString name, qint32 index);
    customWidget *getContactWidget(void);

private:

    customWidget *c_widget;
    QString c_name;
    qint32 c_index;
};

#endif // CONTACT_H
