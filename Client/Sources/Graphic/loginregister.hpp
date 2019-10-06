#ifndef LOGINREGISTER_H
#define LOGINREGISTER_H


#include <QVBoxLayout>
#include <QWidget>
#include "customwidget.hpp"
#include <QFormLayout>
#include <QLineEdit>
#include "QPushButton"
#include "loginform.hpp"
#include "QDebug"
#include "QObject"

namespace Babel {

    namespace Graphic {


        class loginRegister :  public QWidget
        {

            Q_OBJECT

        public:
        /**
            *constructor : build a loginRegister object
        */
            loginRegister();
        /**
            *destructor : destroy a loginRegister object
        */
            ~loginRegister() = default;
        /**
            *get the form widget
            @return _formWidget
        */
            QWidget *getFormWidget() const;
        /**
            *get the register button 
            @return _validate
        */
            QPushButton &getRegisterButton() const;
        /**
            *get the password 
            @return password
        */
            QString getPassword() const;
        /**
            *get the login 
            @return login 
        */
            QString getLogin() const;
        /**
            *set the main form widget 
        */
            void setFormWidget();
        /**
            *set the container layout 
        */
            void setFormCLayout();
        /**
            *set the vertical layout 
        */
            void setFormVLayout();
        /**
            *set the horizontal layout 
        */
            void setFormHLayout();

        private:

            QVBoxLayout *_formLayout = new QVBoxLayout;
            QHBoxLayout *_Horizontal = new QHBoxLayout;
            customWidget *_formWidget;
            QFormLayout *_formForm = new QFormLayout;
            QLineEdit *_formLogin= new QLineEdit;
            QLineEdit *_formPassword= new QLineEdit;
            QPushButton *_validate = new QPushButton("Register");
        };
    }
}

#endif // LOGINREGISTER_H
