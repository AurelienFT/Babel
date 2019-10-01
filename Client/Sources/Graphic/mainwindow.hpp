#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include "customwidget.hpp"
#include "friendlist.hpp"
#include "chat.hpp"
#include "QFormLayout"
#include "home.hpp"
#include "login.hpp"
#include "QStackedWidget"


namespace Babel {

    namespace Graphic {

        class MainWindow : public QMainWindow {

            Q_OBJECT

            public:

                MainWindow(QWidget *parent = nullptr);
                ~MainWindow();

            public slots:

                void slotDisplayFen();

            private:

                QStackedWidget *_windowStack;
                home _homePage;
                login _loginPage;
                int _windowIndex = 0;
        };
    }
}

#endif // MAINWINDOW_H
