#include "mainwindow.hpp"
#include "QDebug"
#include "NetworkClient.hpp"
#include <iostream>

Babel::Graphic::MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), _homePage(), _loginPage()
{
    setWindowTitle("Babel");
    _windowStack = new QStackedWidget(this);
    _windowStack->addWidget(_loginPage.getLoginWidget());
    _windowStack->addWidget(_homePage.getHomeWidget());
    this->setCentralWidget(_windowStack);
    _windowStack->setCurrentIndex(_windowIndex); // on affiche la première fenêtre à l'ouverture du programme
    connect(&_loginPage.form->getValidateButton(), SIGNAL(clicked()), this, SLOT(slotDisplayFen()));
}

Babel::Graphic::MainWindow::~MainWindow() {}

void Babel::Graphic::MainWindow::slotDisplayFen()
{
    _windowIndex = 1;
    std::string username = _loginPage.form->getLogin().toStdString();
    std::string password = _loginPage.form->getPassword().toStdString();
    NetworkClient::instance()->send_server(MessageType::LOGIN, username + "|" + password);
    MessageType returnType = NetworkClient::instance()->receive_messageCode();
    if (returnType == MessageType::OK) {
        if ((_windowIndex < 0) || (_windowIndex > 1)) {return;}
        _windowStack->setCurrentIndex(_windowIndex);
    } else {
        std::cout << "error login" << std::endl;
    }
}

