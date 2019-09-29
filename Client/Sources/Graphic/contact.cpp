#include "contact.hpp"

contact::contact(QString txt, int index, QWidget *parent)
    : QPushButton(parent)
{
    c_txt = txt;
    c_index = index;
    setText(txt);
    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}

void contact::reemitClicked()
{
    emit clicked(c_index);
}

