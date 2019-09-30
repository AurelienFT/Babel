/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** Main
*/

#include "mainwindow.hpp"
#include "NetworkClient.hpp"
#include <QApplication>
#include <iostream>       // std::cout
#include <thread>         // std::thread

void NetworkFunction()
{
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        NetworkClient::instance()->send_server(MessageType::UPDATE_DATA, "");
        MessageType code = NetworkClient::instance()->receive_messageCode();
        std::string reponse = NetworkClient::instance()->getReponse();
        std::cout << "reponse = " << reponse << std::endl;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetworkClient::instance()->connection();
    std::thread network(NetworkFunction);
    MainWindow w;
    w.showMaximized();
    w.show();
    return a.exec();
}
