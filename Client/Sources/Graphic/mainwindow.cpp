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
    QWidget::connect(_homePage.getConversation()->getFriendList()->getSignOut(), SIGNAL(clicked()), this, SLOT(signOut()));
}

Babel::Graphic::MainWindow::~MainWindow() {}

void Babel::Graphic::MainWindow::update()
{
    NetworkClient::instance()->send_server(MessageType::UPDATE_DATA, "");
    MessageType code = NetworkClient::instance()->receive_messageCode();
    std::string reponse = NetworkClient::instance()->getReponse();
    std::string tmp; 
    std::string friendRequest = reponse.substr(0, reponse.find(";"));
    std::string friends = reponse.substr(reponse.find(";") + 1, reponse.length());
    std::stringstream ss1(friendRequest);
    std::stringstream ss2(friends);
    std::vector<std::string> usersFriendRequest;
    std::vector<std::string> userFriends;

    while(std::getline(ss1, tmp, ','))
        usersFriendRequest.push_back(tmp);
    while(std::getline(ss2, tmp, ','))
        userFriends.push_back(tmp);
    _homePage.getConversation()->getFriendList()->setListFriendRequest(usersFriendRequest);
    _homePage.getConversation()->getFriendList()->update(userFriends);
}

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
        QTimer *_timer = new QTimer(this);
        connect(_timer, SIGNAL(timeout()), this, SLOT(update()));
        _timer->start(1000);
    } else {
        std::cout << "error login" << std::endl;
    }
}

void Babel::Graphic::MainWindow::signOut()
{
    _windowIndex = 0;
    NetworkClient::instance()->disconnect();
    _windowStack->setCurrentIndex(_windowIndex);
    NetworkClient::instance()->connection();
}