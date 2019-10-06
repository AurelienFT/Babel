#ifndef FRIENDREQUEST_H
#define FRIENDREQUEST_H
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>


namespace Babel {

    namespace Graphic {

        class friendRequest : public QWidget
        {
            Q_OBJECT

            public:
            /**
                *constructor : build a frienRequest object
                @param index index of the contact
                @param name name of the contact 
            */
                friendRequest(qint32 index, QString name);
            /**
                *destructor : destroy a frienRequest object 
            */
                ~friendRequest() = default;

            signals:
            /**
                *emit clicked signal
                @param digit index of the contact 
            */
                void clicked(int digit);
            /**
                *emit a reject signal
                @param digit index of the contact 
            */
                void reject(int index);

            private slots:
            /**
                *reemite clicked signal 
            */
                void reemitClicked();
            /**
                *reject clicked 
            */
                void rejectClicked();

            private :
                int _index;
                QString _name;
        };
    }
}

#endif // FRIENDREQUEST_H
