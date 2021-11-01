#ifndef APP_H
#define APP_H

#include <QObject>
#include <QDebug>
#include <QLoggingCategory>
#include <QSettings>
#include <watchdog.h>
#include "web_app/web_app.h"

class AppTest : public QObject
{
    Q_OBJECT
public:
    explicit AppTest(bool watchdog=0);
    ~AppTest();

public slots:

private:
    Watchdog        *watchdog;
    WebApp         *web_app;
    Data_storage    *data_storage;
};

#endif
