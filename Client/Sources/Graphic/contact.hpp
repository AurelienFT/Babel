#ifndef CONTACT_H
#define CONTACT_H

#include "customwidget.hpp"
#include "QPushButton"

namespace Babel {

    namespace Graphic {

        class contact : public QPushButton
        {
            Q_OBJECT

            public:
            /**
                *constructor : init a contact object
                @param text name of contact
                @param digit index of contact
                @param parent of contact
            */
                contact(QString txt, int digit, QWidget *parent);
            /**
                *destructor : destroy the contact object
            */
                ~contact() = default;

            signals:
            /**
                *Send a clicked signal
                @param digit index of the contact
            */
                void clicked(int digit);

            private slots:
            /**
                *Send a clicked signal
            */
                void reemitClicked();

            private:
                int c_index;
                QString c_txt;
        };

    }
}

#endif // CONTACT_H
