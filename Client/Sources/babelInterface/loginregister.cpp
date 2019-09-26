#include "loginregister.h"

loginRegister::loginRegister()
{
    setFormWidget();
}

void loginRegister::setFormWidget()
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

void loginRegister::setFormCLayout()
{
    formLayout->addStretch();
    formLayout->addLayout(formForm);
    formLayout->addStretch();
    formLayout->addLayout(Horizontal);
}

void loginRegister::setFormVLayout()
{
    formLogin->setMaximumSize(700, 50);
    formPassword->setMaximumSize(700, 50);
    formForm->addRow("Login :",formLogin);
    formForm->addRow("Password :",formPassword);
}

void loginRegister::setFormHLayout()
{
    validate->setMinimumSize(200,50);
    validate->setStyleSheet("background-color: #ffffff;");

    Horizontal->addStretch();
    Horizontal->addWidget(validate);
    Horizontal->addStretch();
}

// Getter //

QWidget *loginRegister::getFormWidget() const {

    return (formWidget);
}

QPushButton &loginRegister::getRegisterButton()
{
    return (*validate);
}

QString loginRegister::getPassword() const
{
    return (formLogin->text());
}

QString loginRegister::getLogin() const
{
    return (formLogin->text());
}
