#include "friendrequest.hpp"

Babel::Graphic::friendRequest::friendRequest(qint32 index, QString name): _index(index), _name(name)
{
    QPushButton *accept = new QPushButton("ACCEPT");
    QPushButton *reject = new QPushButton("REJECT");
    QHBoxLayout *button = new QHBoxLayout();
    QPushButton *username = new QPushButton(_name);
    QVBoxLayout *v = new QVBoxLayout();
    QWidget *request = new QWidget;

    v->addWidget(username);
    accept->setStyleSheet("border: none; background-color: #2f3136; color: white; font-weight: bold;");
    username->setStyleSheet("border: none; background-color: #2f3136; color:white;font-weight: bold;");
    reject->setStyleSheet("border: none; background-color: #2f3136;color:white;font-weight: bold;");
    connect(accept, SIGNAL(clicked()), this, SLOT(reemitClicked()));
    button->addWidget(accept);
    button->addWidget(reject);
    v->addLayout(button);
    request->setStyleSheet("background-color :#2f3136;");
    this->setLayout(v);
}

void Babel::Graphic::friendRequest::reemitClicked()
{
    emit clicked(_index);
}

