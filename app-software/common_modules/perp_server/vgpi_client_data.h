#if !defined(CLIENT_DATA_H)
#define CLIENT_DATA_H

#include <QTcpSocket>

class VgpiClientData
{
    public:
        enum ClientState {STATE_HANDSHAKE, STATE_WORK, STATE_ERROR};
        QTcpSocket * socket;
        ClientState state;
};

#endif // CLIENT_DATA_H
