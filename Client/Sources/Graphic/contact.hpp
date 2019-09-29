#ifndef CONTACT_H
#define CONTACT_H

#include "customwidget.hpp"
#include "QPushButton"


class contact : public QPushButton
{
    Q_OBJECT

public:
    contact(QString txt,int digit, QWidget *parent);

signals:
    void clicked(int digit);

private slots:
    void reemitClicked();

private:
    int c_index;
    QString c_txt;
};


#endif // CONTACT_H
