#include "loginregister.hpp"

Babel::Graphic::loginRegister::loginRegister()
{
    setFormWidget();
}

void Babel::Graphic::loginRegister::setFormWidget()
{
    QList<qint32> color = {47, 49, 54, 255};
    QPair<qint32, qint32> size(800, 500);
    QPair<qint32, qint32> pos(0, 1);
    setFormVLayout();
    setFormHLayout();
    setFormCLayout();

    formWidget = new customWidget(color, size, pos, nullptr, nullptr);
    formWidget->setMinimumSize(800, 500);
    formWidget->setLayout(formLayout);
}

void Babel::Graphic::loginRegister::setFormCLayout()
{
    formLayout->addStretch();
    formLayout->addLayout(formForm);
    formLayout->addStretch();
    formLayout->addLayout(Horizontal);
}

void Babel::Graphic::loginRegister::setFormVLayout()
{
    formLogin->setMaximumSize(700, 50);
    formPassword->setMaximumSize(700, 50);
    formForm->addRow("Login :",formLogin);
    formForm->addRow("Password :",formPassword);
}

void Babel::Graphic::loginRegister::setFormHLayout()
{
    validate->setMinimumSize(200,50);
    validate->setStyleSheet("background-color: #ffffff;");

    Horizontal->addStretch();
    Horizontal->addWidget(validate);
    Horizontal->addStretch();
}

// Getter //

QWidget *Babel::Graphic::loginRegister::getFormWidget() const {

    return (formWidget);
}

QPushButton &Babel::Graphic::loginRegister::getRegisterButton()
{
    return (*validate);
}

QString Babel::Graphic::loginRegister::getPassword() const
{
    return (formPassword->text());
}

QString Babel::Graphic::loginRegister::getLogin() const
{
    return (formLogin->text());
}
