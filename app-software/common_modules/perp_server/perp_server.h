#ifndef PERP_SERVER_H
#define PERP_SERVER_H

#include <QObject>
#include "vgpi_server.h"

class PerpServer : public Vgpi_server
{
    Q_OBJECT
public:
    explicit PerpServer(int nPort);
    ~PerpServer();

private:
    int port;
    enum {TYPE_KEEPALIVE, TYPE_SET=2};
    void process_message(int type, int type_specific, int value);
    void alive_answer(int type_specific);

signals:
    void signal_btn_pressed(int port, int BtnNum);
    void signal_btn_released(int port, int BtnNum);
};

#endif // PERP_SERVER_H
