#include "loginform.hpp"

loginForm::loginForm()
{
    setFormWidget();
}

void loginForm::setFormWidget() // Set the form widget
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

void loginForm::setFormCLayout() // Set the container Layout
{
    formLayout->addStretch();
    formLayout->addLayout(formForm);
    formLayout->addStretch();
    formLayout->addLayout(Horizontal);
}

void loginForm::setFormVLayout() // Set the vertical layout
{
    formLogin->setMaximumSize(700, 50);
    formPassword->setMaximumSize(700, 50);
    formForm->addRow("Login :",formLogin);
    formForm->addRow("Password :",formPassword);
}

void loginForm::setFormHLayout() // Set the horizontal Layout
{
    validate->setMinimumSize(200,50);
    validate->setStyleSheet("background-color: #ffffff;");

    Horizontal->addStretch();
    Horizontal->addWidget(validate);
    Horizontal->addStretch();
}

// Getter //

QWidget *loginForm::getFormWidget() const {

    return (formWidget);
}

QPushButton &loginForm::getValidateButton()
{
    return (*validate);
}

QString loginForm::getPassword() const
{
    return (formPassword->text());
}

QString loginForm::getLogin() const
{
    return (formLogin->text());
}


