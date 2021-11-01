#ifndef UPTIME_UTILS_H
#define UPTIME_UTILS_H

#include <QObject>

class Uptime_utils : public QObject
{
    Q_OBJECT
public:
    static QString get_sys_uptime();
    static int32_t get_time_t();
    static void reboot();
    static void system_set_time(time_t time);

signals:

public slots:

private:

};

#endif // UPTIME_UTILS_H
