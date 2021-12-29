#include "perp_server.h"

PerpServer::PerpServer(int nPort) :
    Vgpi_server(nPort),
    port(nPort)
{
    std::fill(led_state.begin(), led_state.end(), LED_OFF);
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
            emit signal_btn_pressed(port, type_specific-1);
        else
            emit signal_btn_released(port, type_specific-1);
    }
}

void PerpServer::alive_answer(int type_specific)
{
    QByteArray arr;

    if(type_specific != 0) return;
    arr = vgpi_frame_get_answer(0, 0);
    sendToAllConnections(arr);
}

void PerpServer::set_led(uint ledNum, ledColor_t state)
{
    if(ledNum >= led_state.size()) return;
    led_state[ledNum] = state;

    QByteArray arr = vgpi_frame_uint16(ledNum+1, state);
    sendToAllConnections(arr);
}

void PerpServer::set_led_state(VgpiClientData * client)
{
    QByteArray arr;
    for(uint i = 0; i < led_state.size(); i++){
        arr = vgpi_frame_uint16(i + 1, led_state[i]);
        sendClient(client->socket, arr);
    }
}

void PerpServer::signal_new_client(VgpiClientData * client)
{
    set_led_state(client);
}
