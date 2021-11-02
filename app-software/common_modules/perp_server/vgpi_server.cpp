#include "vgpi_server.h"

static QLoggingCategory category("Vgpi Server");

#define PROTOCOL_VERSION_MAJOR 1
#define PROTOCOL_VERSION_MINOR 0
#define PROTOCOL_VERSION_REV   0

Vgpi_server::Vgpi_server(int nPort)
{
    qCDebug(category) << "creating...";

    handshakeBlock.resize(8);
    handshakeBlock[0] = 'P';
    handshakeBlock[1] = 'E';
    handshakeBlock[2] = 'R';
    handshakeBlock[3] = 'P';
    handshakeBlock[4] = 0x00;
    handshakeBlock[5] = PROTOCOL_VERSION_MAJOR;
    handshakeBlock[6] = PROTOCOL_VERSION_MINOR;
    handshakeBlock[7] = PROTOCOL_VERSION_REV;

    tcpServer = new QTcpServer(this);

    if(!tcpServer->listen(QHostAddress::Any, nPort)) {

        qCDebug(category) << "Server Error. Unable to start the server:"
            << tcpServer->errorString();
        tcpServer->close();
        return;
    }

    connect(tcpServer, &QTcpServer::newConnection, this, &Vgpi_server::slotNewConnection);

}

Vgpi_server::~Vgpi_server()
{
    clientConnections.clear();

    tcpServer->close();
    delete  tcpServer;
}

void Vgpi_server::slotNewConnection()
{
    QTcpSocket* pClientSocket = tcpServer->nextPendingConnection();
    connect(pClientSocket, &QTcpSocket::disconnected, pClientSocket, &QTcpSocket::deleteLater);
    connect(pClientSocket, &QTcpSocket::readyRead,    this,          &Vgpi_server::slotReadClient);
    connect(pClientSocket, &QTcpSocket::disconnected, this,          &Vgpi_server::slotDisconnected);

    QHostAddress peer_ip = pClientSocket->peerAddress();

    VgpiClientData * client = new VgpiClientData;
    client->socket = pClientSocket;
    client->state = VgpiClientData::STATE_HANDSHAKE;

    clientConnections << client;

    signal_new_client(pClientSocket);
}

void Vgpi_server::sendClient(QTcpSocket* pSocket, QByteArray arrBlock)
{
    pSocket->write(arrBlock);
}

void Vgpi_server::slotReadClient()
{
    VgpiClientData * client = getClietnData((QTcpSocket*)sender());

    while(read_msg(client));

}

int Vgpi_server::read_msg(VgpiClientData * client)
{
    int ret = 0;
    switch(client->state){
        case VgpiClientData::STATE_HANDSHAKE:
            if(client->socket->bytesAvailable()>=HANDSHAKE_SIZE){
                QByteArray data = client->socket->read(HANDSHAKE_SIZE);
                if(handshake_check(data)){
                    client->state=VgpiClientData::STATE_WORK;
                    client->socket->write(handshakeBlock);
                }else{
                    client->state=VgpiClientData::STATE_ERROR;
                }
                ret = 1;
            }
            break;
        case VgpiClientData::STATE_WORK:
            if(client->socket->bytesAvailable()>=HEADER_SIZE){
                QByteArray data = client->socket->peek(HEADER_SIZE);
                int size = vgpi_get_packet_size(data);
                if(client->socket->bytesAvailable()>=size){
                    QByteArray data = client->socket->read(size);
                    parse_message(data);
                    ret = 1;
                }
            }
            break;
        case VgpiClientData::STATE_ERROR:
            client->socket->readAll();
            break;
    }
    return ret;
}

void Vgpi_server::sendToAllConnections(QByteArray arrBlock)
{
    foreach(VgpiClientData *clientConnection, clientConnections) {
       clientConnection->socket->write(arrBlock);
    }
}

VgpiClientData * Vgpi_server::getClietnData(QTcpSocket* socket)
{
    for(VgpiClientData * i : clientConnections){
        if(socket==i->socket){
            return i;
        }
    }
    Q_ASSERT(0);
    return 0;
}

void Vgpi_server::slotDisconnected()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();

    VgpiClientData * client = getClietnData(pClientSocket);

    clientConnections.removeAll(client);
    delete client;
}

void Vgpi_server::slot_close_connection(QTcpSocket* pSocket)
{
    pSocket->close();
}

int Vgpi_server::handshake_check(QByteArray data)
{
    return data == handshakeBlock;
}


void Vgpi_server::parse_message(QByteArray data)
{
    int type, type_specific, type_data;
    type = vgpi_get_packet_type(data);
    type_specific = vgpi_get_type_specific(data);

    QByteArray payload = vgpi_get_data(data, type_data);

    int value = 0;
    switch (type_data) {
    case VGPI_FIELD_UINT16:
        value = vgpi_to_int16(payload);
        break;
    case VGPI_FIELD_INT32:
        value = vgpi_to_int32(payload);
        break;
    default:
        break;
    }

    process_message(type, type_specific, value);
}
