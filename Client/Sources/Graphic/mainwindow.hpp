#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <sstream>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QTimer>
#include "customwidget.hpp"
#include "friendlist.hpp"
#include "chat.hpp"
#include "QFormLayout"
#include "home.hpp"
#include "login.hpp"
#include "QStackedWidget"
#include "VoIpClient.hpp"


namespace Babel {

    namespace Graphic {

        class MainWindow : public QMainWindow {

            Q_OBJECT

            public:
            /**
                *constructor : build a mainWindow object
            */
                MainWindow(QWidget *parent = nullptr);
            /**
                *destructor : destroy a mainWindow object
            */
                ~MainWindow();

            public slots:
            /**
                *change the view of the window
            */
                void slotDisplayFen();
            /**
                *update the window
            */
                void update();
            /**
                *signout manager
            */
                void signOut();

            private:

                QStackedWidget *_windowStack;
                home _homePage;
                login _loginPage;
                int _windowIndex = 0;
                QTimer *_timer;
                VoIpNetwork::VoIpClient *_clientAudio;
        };
    }
}

#endif // MAINWINDOW_H
