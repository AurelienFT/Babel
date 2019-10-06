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

    _formWidget = new customWidget(color, size, pos, nullptr, nullptr);
    _formWidget->setMinimumSize(800, 500);
    _formWidget->setLayout(_formLayout);
}

void Babel::Graphic::loginRegister::setFormCLayout()
{
    _formLayout->addStretch();
    _formLayout->addLayout(_formForm);
    _formLayout->addStretch();
    _formLayout->addLayout(_Horizontal);
}

void Babel::Graphic::loginRegister::setFormVLayout()
{
    _formLogin->setMaximumSize(700, 50);
    _formPassword->setMaximumSize(700, 50);
    _formForm->addRow("Login :", _formLogin);
    _formForm->addRow("Password :", _formPassword);
}

void Babel::Graphic::loginRegister::setFormHLayout()
{
    _validate->setMinimumSize(200,50);
    _validate->setStyleSheet("background-color: #ffffff;");

    _Horizontal->addStretch();
    _Horizontal->addWidget(_validate);
    _Horizontal->addStretch();
}

// Getter //

QWidget *Babel::Graphic::loginRegister::getFormWidget() const 
{
    return (_formWidget);
}

QPushButton &Babel::Graphic::loginRegister::getRegisterButton() const
{
    return (*_validate);
}

QString Babel::Graphic::loginRegister::getPassword() const
{
    return (_formPassword->text());
}

QString Babel::Graphic::loginRegister::getLogin() const
{
    return (_formLogin->text());
}
