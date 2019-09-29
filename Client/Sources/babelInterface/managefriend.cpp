#include "managefriend.h"
#include "iostream"

ManageFriend::ManageFriend()
{
    setFormWidget();
}

void ManageFriend::setFormWidget()
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

void ManageFriend::setFormCLayout()
{
    formLayout->addStretch();
    formLayout->addLayout(formForm);
    formLayout->addStretch();
    formLayout->addLayout(Horizontal);
}

void ManageFriend::setFormVLayout()
{
    formLogin->setMaximumSize(700, 50);
    formPassword->setMaximumSize(700, 50);
    formLogin->setText("Name");
    formForm->addRow("",formLogin);
}

void ManageFriend::setFormHLayout()
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

QWidget *ManageFriend::getFormWidget() const
{

    return (formWidget);
}

void ManageFriend::addFriend()
{
    std::cout << "add" << std::endl;
    formLogin->text();
}

void ManageFriend::removeFriend()
{
    std::cout << "remove" << std::endl;
}
