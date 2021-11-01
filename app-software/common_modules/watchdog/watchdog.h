#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <QTimer>
#include <QObject>

class Watchdog : public QObject
{
        Q_OBJECT
public:
        explicit Watchdog(int enable = 1);
        ~Watchdog();
        void stop();
private:
        QTimer timer;
        int watchdog_fh;
private Q_SLOTS:
        void watchdog_kick();
};

#endif
