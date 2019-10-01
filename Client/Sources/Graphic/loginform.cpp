#include "loginform.hpp"

Babel::Graphic::loginForm::loginForm()
{
    setFormWidget();
}

void Babel::Graphic::loginForm::setFormWidget() // Set the form widget
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

void Babel::Graphic::loginForm::setFormCLayout() // Set the container Layout
{
    formLayout->addStretch();
    formLayout->addLayout(formForm);
    formLayout->addStretch();
    formLayout->addLayout(Horizontal);
}

void Babel::Graphic::loginForm::setFormVLayout() // Set the vertical layout
{
    formLogin->setMaximumSize(700, 50);
    formPassword->setMaximumSize(700, 50);
    formForm->addRow("Login :",formLogin);
    formForm->addRow("Password :",formPassword);
}

void Babel::Graphic::loginForm::setFormHLayout() // Set the horizontal Layout
{
    validate->setMinimumSize(200,50);
    validate->setStyleSheet("background-color: #ffffff;");
    Horizontal->addStretch();
    Horizontal->addWidget(validate);
    Horizontal->addStretch();
}

// Getter /

QWidget *Babel::Graphic::loginForm::getFormWidget() const {

    return (formWidget);
}

QPushButton &Babel::Graphic::loginForm::getValidateButton()
{
    return (*validate);
}

QString Babel::Graphic::loginForm::getPassword() const
{
    return (formPassword->text());
}

QString Babel::Graphic::loginForm::getLogin() const
{
    return (formLogin->text());
}


