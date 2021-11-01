#include <sys/time.h>
#include <QJsonParseError>
#include "web_app.h"

static QLoggingCategory category("Web_App");

WebApp::WebApp(Data_storage * data_storage):
    WebSocketServer(),
    data_storage(data_storage)
{
    qDebug(category) << "Creating...";

    connect(data_storage, &Data_storage::signal_data_changed, this, &WebApp::slot_storage_commit);
}

WebApp::~WebApp()
{
}

QJsonObject WebApp::get_json_device_settings()
{
    QJsonObject data_obj;

    return data_obj;
}

QByteArray WebApp::get_web_device_settings()
{
    return json_to_bytes("device_settings", get_json_device_settings());
}

void WebApp::slot_storage_commit(QString key)
{
    if(key == "signal_channel_settings")
        sendall(get_web_device_settings());
}

void WebApp::slot_web_new_client(QWebSocket *pClient)
{
    senddata(pClient, get_web_device_settings());
}

QByteArray WebApp::api_req(QString url, QString  method, QByteArray body)
{
    QJsonObject ret;

    if(url == "/api/device_settings")
        ret = get_json_device_settings();
    else
        ret = get_json_device_settings();
    
    return json_to_bytes(ret);
};
