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

    formWidget = new customWidget(color, size, pos, nullptr, nullptr);
    formWidget->setMinimumSize(800, 500);
    h->addStretch();
    h->addLayout(formLayout);
    h->addStretch();
    v->addStretch();
    v->addLayout(h);
    v->addStretch();
    formWidget->setLayout(v);
}

void Babel::Graphic::ManageFriend::setFormCLayout()
{
    formLayout->addStretch();
    formLayout->addLayout(formForm);
    formLayout->addStretch();
    formLayout->addLayout(Horizontal);
}

void Babel::Graphic::ManageFriend::setFormVLayout()
{
    formLogin->setMaximumSize(700, 50);
    formPassword->setMaximumSize(700, 50);
    formLogin->setText("Name");
    formForm->addRow("",formLogin);
}

void Babel::Graphic::ManageFriend::setFormHLayout()
{
    add->setMinimumSize(200,50);
    add->setStyleSheet("background-color: #ffffff;");
    remove->setMinimumSize(200,50);
    remove->setStyleSheet("background-color: #ffffff;");

    Horizontal->addStretch();
    Horizontal->addWidget(add);
    Horizontal->addWidget(remove);
    Horizontal->addStretch();
    connect(add, SIGNAL(clicked()), this, SLOT(addFriend()));
    connect(remove, SIGNAL(clicked()), this, SLOT(removeFriend()));
}

QWidget *Babel::Graphic::ManageFriend::getFormWidget() const
{

    return (formWidget);
}

void Babel::Graphic::ManageFriend::addFriend()
{
    std::string friendName = formLogin->displayText().toStdString();
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
