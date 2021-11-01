#ifndef UPTIME_UTILS_H
#define UPTIME_UTILS_H

#include <QObject>

class Uptime_utils : public QObject
{
    Q_OBJECT
public:
    static QString get_sys_uptime();
    static int32_t get_time_t();

signals:

public slots:

private:

};

#endif // UPTIME_UTILS_H
