#ifndef EVENTLOG_H
#define EVENTLOG_H

#include <QtCore/QObject>

class Eventlog : public QObject
{
        Q_OBJECT
public:

    void add(int category, QString message);
     Eventlog();
     ~Eventlog();
};


#endif
