#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Babel::Graphic::MainWindow w;
    w.showMaximized();
    w.show();
    return a.exec();
}
