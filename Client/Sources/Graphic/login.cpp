#include "login.hpp"
#include "QDebug"
#include <iostream>
#include "NetworkInterface.hpp"
#include "NetworkClient.hpp"

Babel::Graphic::login::login()
{
    QList<qint32> color = {32, 34, 37, 255};
    QPair<qint32, qint32> size(1920, 1080);
    QPair<qint32, qint32> pos(0, 0);

    _loginLayout = new QVBoxLayout();
    _loginWidget = new customWidget(color, size, pos, nullptr, nullptr);
    _loginBar = new QTabBar();
    setLoginWidget();
}


void Babel::Graphic::login::setLoginWidget()
{
    setLoginBar();
    setLoginVLayout();
    setLoginHLayout();
    _loginLayout->addWidget(_loginBar);
    _loginLayout->addLayout(_formLayout);
    _loginWidget->setLayout(_loginLayout);
    connect(&formRegister->getRegisterButton(), SIGNAL(clicked()), this, SLOT(goToLogin()));
}

void Babel::Graphic::login::setLoginHLayout()
{
    _formLayout->addStretch();
    _formLayout->addLayout(_vLayout);
    _formLayout->addStretch();
}

void Babel::Graphic::login::setLoginVLayout()
{
    _stack->addWidget(form->getFormWidget());
    _stack->addWidget(formRegister->getFormWidget());
    _vLayout->addStretch();
    _vLayout->addWidget(_stack);
    _vLayout->addStretch();
}

void Babel::Graphic::login::setLoginBar()
{
    _loginBar->addTab("Connection");
    _loginBar->addTab("Registration");
    _loginBar->setDrawBase(false);
    _loginBar->setStyleSheet("QTabBar::tab { max-width: 0px; height : 28px; border: 1px; color: #ffffff; background-color: #36393f; font-weight: bold}"
                             "QTabBar::tab:selected { max-width: 0px; height : 30px; border: 0px; color: #ffffff; background-color: #f26522}" );
     connect(_loginBar, SIGNAL(currentChanged(int)), this, SLOT(setLoginLayout()));
}


Babel::Graphic::customWidget *Babel::Graphic::login::getLoginWidget() const {

    return(_loginWidget);
}

// Private Slots//

void Babel::Graphic::login::setLoginLayout() // Change le contenu de la fenêtre de login en fonction de la TabBar//
{
    if (_loginBar->currentIndex() == 0)
        _stack->setCurrentIndex(0);
    else if (_loginBar->currentIndex() == 1)
        _stack->setCurrentIndex(1);
}

void Babel::Graphic::login::goToLogin() // Fonction pour aller à la feneêtre de connection //
{
    std::string login = formRegister->getLogin().toStdString();
    std::string password = formRegister->getPassword().toStdString();
    NetworkClient::instance()->send_server(MessageType::REGISTER, login + "|" + password);
    MessageType type = NetworkClient::instance()->receive_messageCode();
    std::cout << "type: " << static_cast<int>(type) << std::endl;
    _loginBar->setCurrentIndex(0);
    _stack->setCurrentIndex(0);
}




