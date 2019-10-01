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
                friendRequest(qint32 index, QString name);
                void clearLayout(QLayout *layout);

            signals:
                void clicked(int digit);

            private slots:
                void reemitClicked();

            private :
                int _index;
                QString _name;
        };
    }
}

#endif // FRIENDREQUEST_H
