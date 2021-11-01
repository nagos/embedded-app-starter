#include "app.h"
#include "version.h"

static QLoggingCategory category("APPTEST");

AppTest::AppTest(bool watchdog)
{
    qDebug(category) << "Program start";

    this->watchdog = new Watchdog(watchdog);

    data_storage = new Data_storage;

    web_app = new WebApp(data_storage);

}

AppTest::~AppTest()
{
    delete watchdog;
    delete web_app;
    delete data_storage;
}
