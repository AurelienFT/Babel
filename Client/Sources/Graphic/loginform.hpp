#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QVBoxLayout>
#include <QWidget>
#include "customwidget.hpp"
#include <QFormLayout>
#include <QLineEdit>
#include "QPushButton"

namespace Babel {

    namespace Graphic {

        class loginForm :  public QWidget
        {

            Q_OBJECT

        public:
        /**
            *constructor : build a loginForm object
        */
            loginForm();
        /**
            *destructor : destroy a loginForm object
        */
            ~loginForm() = default;
        /**
            *get form widget
            @return _formForm
        */
            QWidget *getFormWidget() const;
        /**
            *get validate button
            @return  *_validate
        */
            QPushButton &getValidateButton() const ;
        /**
            *get password 
            @return password 
        */
            QString getPassword() const;
        /**
            *get login
            @return login 
        */
            QString getLogin() const;
        /**
            *set form widget 
        */
            void setFormWidget();
        /**
            *set container layout 
        */
            void setFormCLayout();
        /**
            *set vertical layout  
        */
            void setFormVLayout();
        /**
            *set horizontal layout  
        */
            void setFormHLayout();

        private:

            QVBoxLayout *_formLayout = new QVBoxLayout;
            QHBoxLayout *_Horizontal = new QHBoxLayout;
            customWidget *_formWidget;
            QFormLayout *_formForm = new QFormLayout;
            QLineEdit *_formLogin= new QLineEdit;
            QLineEdit *_formPassword= new QLineEdit;
            QPushButton *_validate = new QPushButton("Validate");
        };
    }
}

#endif // LOGINFORM_H
