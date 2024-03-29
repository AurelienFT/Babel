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

int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);
        NetworkClient::instance()->connection();
        Babel::Graphic::MainWindow w;
        w.showMaximized();
        w.show();
        return a.exec();
    } catch (std::exception &e) {
        std::cerr << "Error in client" << std::endl;
        return (84);
    }
}
