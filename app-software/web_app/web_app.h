#ifndef WEB_APP
#define WEB_APP

#include <QLoggingCategory>
#include <QTimer>
#include <common_modules.h>

class WebApp: public WebSocketServer
{
    Q_OBJECT
public:
    WebApp(Data_storage * data_storage);
    ~WebApp();


public slots:
    void slot_storage_commit(QString key);

private:
    QJsonObject get_json_device_settings();
    QByteArray  get_web_device_settings();
    QByteArray api_req(QString url, QString  method, QByteArray body);
    void slot_web_new_client(QWebSocket *pClient);
    Data_storage *data_storage;
};

#endif // WEB_APP
