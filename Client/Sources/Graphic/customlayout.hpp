#ifndef CUSTOMLAYOUT_H
#define CUSTOMLAYOUT_H

#include <QObject>

class customLayout : public QVBoxLayout
{

public:
    /**
        *constructor : build a customLayout object 
    */
    customLayout();
    /**
        *destructor : destroy a customLayout object
    */
   ~customLayout();

private:

    QString _title;
};

#endif // CUSTOMLAYOUT_H