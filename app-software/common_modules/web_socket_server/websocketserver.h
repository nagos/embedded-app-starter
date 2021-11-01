#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QList>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>

#ifdef WITH_TUFAO
#include <Tufao/HttpServer>
#include <QtCore/QUrl>
#include <Tufao/HttpServerRequest>
#include <Tufao/Headers>
#include <Tufao/HttpFileServer>
#endif


QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class WebSocketServer : public QObject
{
        Q_OBJECT
public:
        explicit WebSocketServer(quint16 port=8080, bool debug = false, QObject *parent = Q_NULLPTR);
        ~WebSocketServer();

        void senddata(QWebSocket *pClient, QByteArray data);
        void sendall(QByteArray data);
        int get_int_value(QJsonObject obj, QString name){
                return get_value<int>(obj, name);
        };
        QString get_str_value(QJsonObject obj, QString name){
                return get_value<QString>(obj, name);
        };
        int get_bool_value(QJsonObject obj, QString name){
                return get_value<int>(obj, name);
        };
        template <typename T> T get_value(QJsonObject obj, QString name){
                return obj.value(name).toVariant().value<T>();
        };
        QJsonArray get_json_Array(QJsonObject obj, QString name);
        QJsonObject get_json_object(QJsonObject obj, QString name);

Q_SIGNALS:
        void closed();

signals:
        void signal_web_new_client( QWebSocket *pSocket );
        void signal_web_message( QWebSocket *pSocket, QJsonObject val);

private Q_SLOTS:
        void onNewConnection();
        void parse_message(QWebSocket *pClient, QString data);
        void processTextMessage(QString message);
        void socketDisconnected();
        QByteArray get_alive();
        virtual void slot_web_new_client(QWebSocket *pClient){};
        virtual void slot_web_message(QString name, QJsonObject data, QWebSocket *pClient){};
        #ifdef WITH_TUFAO
        void slot_server_ready(Tufao::HttpServerRequest &request, Tufao::HttpServerResponse &response);
        #endif

private:
        QWebSocketServer *m_pWebSocketServer;
        QList<QWebSocket *> m_clients;
        bool m_debug;
        #ifdef WITH_TUFAO
        Tufao::HttpServer server;
        #endif
        void init_http_server();
protected:
        int rand_value;
        QByteArray json_to_bytes(QString msg_type, QJsonObject data_obj);
        QByteArray json_to_bytes(QJsonObject data_obj);
        template <size_t N> void read_array(QJsonObject &data_obj, QString name, std::array<int,N> &ret){
                QJsonArray jsonArray = get_value<QJsonArray>(data_obj, name);
                if(ret.size()!=(uint)jsonArray.size())
                        return;
                for(size_t i=0; i<N; i++)
                        ret[i] = jsonArray[i].toInt();
        }
        template <size_t N, typename T> QJsonArray write_array(std::array<T,N> data){
                QJsonArray ret;

                for(T i : data)
                        ret.append(i);

                return ret;
        };
        virtual QByteArray api_req(QString url, QString  method, QByteArray body);
};

#endif
