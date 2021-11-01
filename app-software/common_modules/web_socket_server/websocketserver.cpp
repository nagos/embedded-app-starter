#include "websocketserver.h"
#include <QtWebSockets/QtWebSockets>
#include <QDebug>
#include <cstdlib>
#include <QJsonDocument>

QT_USE_NAMESPACE

#define HTTP_PORT 8082

/**
*  Конструктор
**/
WebSocketServer::WebSocketServer(quint16 port, bool debug, QObject *parent) :
        QObject(parent),
        m_pWebSocketServer(new QWebSocketServer(QStringLiteral("App Server"),
                QWebSocketServer::NonSecureMode, this)),
        m_clients(),
        m_debug(debug)
{
        if (m_pWebSocketServer->listen(QHostAddress::Any, port)){
                if (m_debug)
                        qDebug() << "WebSocketServer listening on port" << port;
                connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                        this, &WebSocketServer::onNewConnection);
                connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WebSocketServer::closed);
        }
        rand_value = std::rand();
        #ifdef WITH_TUFAO
        init_http_server();
        #endif
}

WebSocketServer::~WebSocketServer()
{
        m_pWebSocketServer->close();
        qDeleteAll(m_clients.begin(), m_clients.end());
}

/**
*  Обработчик нового соединения
**/
void WebSocketServer::onNewConnection()
{
        QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

        connect(pSocket, &QWebSocket::textMessageReceived, this, &WebSocketServer::processTextMessage);
        connect(pSocket, &QWebSocket::disconnected, this, &WebSocketServer::socketDisconnected);

        m_clients << pSocket;

        slot_web_new_client(pSocket);
}

/**
*  Отправить данные одному клиенту
**/
void WebSocketServer::senddata(QWebSocket *pClient, QByteArray data)
{
        pClient->sendTextMessage(data);
}

/**
*  Отправить данные всем клиентам
**/
void WebSocketServer::sendall(QByteArray data)
{
    QList<QWebSocket *>::iterator i;
    for (i = m_clients.begin(); i != m_clients.end(); ++i){
            senddata(*i, data);
    }
}

/**
*  Генерирует ответное json сообщение
*  проверки соединения
**/
QByteArray WebSocketServer::get_alive()
{
        QJsonObject data_obj;

        data_obj["status"] = "alive";

        return json_to_bytes("keepalive", data_obj);
}

/**
*  Разбор входящего сообщения
**/
void WebSocketServer::parse_message(QWebSocket *pClient, QString data)
{
        QJsonObject data_obj;
        QJsonParseError err;

        QJsonDocument json = QJsonDocument::fromJson(data.toUtf8(), &err);
        QJsonObject    obj = json.object();
        QJsonValue     val = obj.value("type");

        if(val.toString() == "keepalive"){
                senddata(pClient, get_alive());
                return;
        }

        val = obj.value("type");
        if(val.isString())
                slot_web_message(val.toString(),  obj.value("data").toObject(), pClient);
}

/**
** Получено новое сообщение
**/
void WebSocketServer::processTextMessage(QString message)
{
        QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

        if (m_debug)
                qDebug() << "Message received:" << message;

        parse_message(pClient, message);
}

/**
*  Отключение клиента
**/
void WebSocketServer::socketDisconnected()
{
        QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
        if (m_debug)
                qDebug() << "socketDisconnected:" << pClient;
        if (pClient){
                m_clients.removeAll(pClient);
                pClient->deleteLater();
        }
}

template <> QJsonObject WebSocketServer::get_value<QJsonObject>(QJsonObject obj, QString name){
        return obj.value(name).toObject();
};

template <> QJsonArray WebSocketServer::get_value<QJsonArray>(QJsonObject obj, QString name){
        return obj.value(name).toArray();
};

QJsonArray WebSocketServer::get_json_Array(QJsonObject obj, QString name)
{
        return get_value<QJsonArray>(obj, name);
}

QJsonObject WebSocketServer::get_json_object(QJsonObject obj, QString name)
{
        return get_value<QJsonObject>(obj, name);
}

QByteArray WebSocketServer::json_to_bytes(QString msg_type, QJsonObject data_obj)
{
        QJsonObject json;

        json["type"] = msg_type;
        json["data"] = data_obj;
        QJsonDocument saveDoc(json);

        return saveDoc.toJson();
}

QByteArray WebSocketServer::json_to_bytes(QJsonObject data_obj)
{
        QJsonDocument saveDoc(data_obj);
        return saveDoc.toJson();
}

#ifdef WITH_TUFAO
void WebSocketServer::init_http_server()
{
        
        connect(&server, &Tufao::HttpServer::requestReady, this,
                &WebSocketServer::slot_server_ready);

        server.listen(QHostAddress::Any, HTTP_PORT);
}

void WebSocketServer::slot_server_ready(Tufao::HttpServerRequest &request, Tufao::HttpServerResponse &response)
{
        QString req_url, req_method;
        QByteArray req_body;
        req_url     = request.url().toString();
        req_method  = request.method();
        req_body    = request.readBody();

        QByteArray ans = api_req(req_url, req_method, req_body);
        response.writeHead(Tufao::HttpResponseStatus::OK);
        response.headers().replace("Content-Type", "application/json");
        response.headers().replace("Access-Control-Allow-Origin", "*");
        response.headers().replace("Access-Control-Allow-Headers", "*");
        response.end(ans);
}

#endif

QByteArray WebSocketServer::api_req(QString url, QString  method, QByteArray body)
{
    return "";
};
