#include "perp_server.h"

PerpServer::PerpServer(int nPort) :
    Vgpi_server(nPort),
    port(nPort)
{
}

PerpServer::~PerpServer()
{
}

void PerpServer::process_message(int type, int type_specific, int value)
{
    if(type == TYPE_KEEPALIVE)
        alive_answer(type_specific);
    else if(type == TYPE_SET){
        if(value)
            emit signal_btn_pressed(port, type_specific);
        else
            emit signal_btn_released(port, type_specific);
    }
}

void PerpServer::alive_answer(int type_specific)
{
    QByteArray arr;

    if(type_specific != 0) return;
    arr = vgpi_frame_get_answer(0, 0);
    sendToAllConnections(arr);
}
