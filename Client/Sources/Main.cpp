/*
** EPITECH PROJECT, 2019
** cpp_babel_2019
** File description:
** Main
*/

#include "mainwindow.hpp"
#include "NetworkClient.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetworkClient::instance()->connection();
    MainWindow w;
    w.showMaximized();
    w.show();
    return a.exec();
}
