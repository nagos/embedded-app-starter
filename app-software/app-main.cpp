#include <QCoreApplication>
#include <signal.h>
#include <QCommandLineParser>
#include <QDebug>
#include <QObject>
#include "app.h"

QT_USE_NAMESPACE

void app_exit(int)
{
        QCoreApplication::quit();
}

int main(int argc, char *argv[])
{
        QCoreApplication a(argc, argv);
        qDebug() << "APP-TEST application";
        QCommandLineParser parser;
        QCommandLineOption watchdog_option("w", "watchdog");
        parser.setApplicationDescription("APP-TEST applicaton");
        parser.addOption(watchdog_option);
        parser.addHelpOption();
        parser.process(a);

        signal(SIGINT, app_exit);
        signal(SIGPIPE, SIG_IGN);

        bool watchdog = parser.isSet(watchdog_option);
        AppTest app(watchdog);

        return a.exec();
}
