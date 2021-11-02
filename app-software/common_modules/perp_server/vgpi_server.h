#ifndef VGPI_SERVER_H
#define VGPI_SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QLoggingCategory>
#include "vgpi_api.h"
#include "vgpi_client_data.h"

class Vgpi_server : public Vgpi_api
{
    Q_OBJECT
public:
    explicit Vgpi_server(int nPort);
    ~Vgpi_server();
    void sendToAllConnections(QByteArray arrBlock);
    void sendClient(QTcpSocket* pSocket, QByteArray arrBlock);


private:
    QTcpServer *tcpServer;
    QList<VgpiClientData *> clientConnections;
    QByteArray handshakeBlock;
    VgpiClientData * getClietnData(QTcpSocket* socket);
    int handshake_check(QByteArray data);
    int read_msg(VgpiClientData * client);
    void parse_message(QByteArray data);

protected:
    virtual void signal_new_client(QTcpSocket* pSocket){};
    virtual void signal_pDisconnected(QTcpSocket* pSocket){};
    virtual void process_message(int type, int type_specific, int value){};

public slots:
    void slotNewConnection();
    void slotReadClient   ();
    void slotDisconnected();
    void slot_close_connection(QTcpSocket* pSocket);

};

#endif // VGPI_SERVER_H
