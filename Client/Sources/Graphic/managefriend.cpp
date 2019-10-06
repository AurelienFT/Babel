#include "managefriend.hpp"
#include "iostream"
#include "NetworkInterface.hpp"
#include "NetworkClient.hpp"

Babel::Graphic::ManageFriend::ManageFriend()
{
    setFormWidget();
}

void Babel::Graphic::ManageFriend::setFormWidget()
{
    QList<qint32> color = {47, 49, 54, 255};
    QPair<qint32, qint32> size(1920, 1080);
    QPair<qint32, qint32> pos(0, 1);
    QHBoxLayout *h = new QHBoxLayout();
    QVBoxLayout *v = new QVBoxLayout();
    setFormVLayout();
    setFormHLayout();
    setFormCLayout();

    _formWidget = new customWidget(color, size, pos, nullptr, nullptr);
    _formWidget->setMinimumSize(800, 500);
    h->addStretch();
    h->addLayout(_formLayout);
    h->addStretch();
    v->addStretch();
    v->addLayout(h);
    v->addStretch();
    _formWidget->setLayout(v);
}

void Babel::Graphic::ManageFriend::setFormCLayout()
{
    _formLayout->addStretch();
    _formLayout->addLayout(_formForm);
    _formLayout->addStretch();
    _formLayout->addLayout(_Horizontal);
}

void Babel::Graphic::ManageFriend::setFormVLayout()
{
    _formLogin->setMaximumSize(700, 50);
    _formPassword->setMaximumSize(700, 50);
    _formLogin->setText("Name");
    _formForm->addRow("", _formLogin);
}

void Babel::Graphic::ManageFriend::setFormHLayout()
{
    _add->setMinimumSize(200,50);
    _add->setStyleSheet("background-color: #ffffff;");
    _remove->setMinimumSize(200,50);
    _remove->setStyleSheet("background-color: #ffffff;");

    _Horizontal->addStretch();
    _Horizontal->addWidget(_add);
    _Horizontal->addWidget(_remove);
    _Horizontal->addStretch();
    connect(_add, SIGNAL(clicked()), this, SLOT(addFriend()));
    connect(_remove, SIGNAL(clicked()), this, SLOT(removeFriend()));
}

QWidget *Babel::Graphic::ManageFriend::getFormWidget() const
{

    return (_formWidget);
}

void Babel::Graphic::ManageFriend::addFriend()
{
    std::string friendName = _formLogin->displayText().toStdString();
    NetworkClient::instance()->send_server(MessageType::ADD_FRIEND, friendName);
    MessageType returnType = NetworkClient::instance()->receive_messageCode();
    if (returnType == MessageType::OK) {
        std::cout << "friend request sent" << std::endl;
    } else {
        std::cout << "error user not exist" << std::endl;
    }
}

void Babel::Graphic::ManageFriend::removeFriend()
{
    std::cout << "remove" << std::endl;
}
