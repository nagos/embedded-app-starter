#ifndef PERP_SERVER_H
#define PERP_SERVER_H

#include <QObject>
#include "vgpi_server.h"

class PerpServer : public Vgpi_server
{
    Q_OBJECT
public:
    enum ledColor_t{LED_OFF, LED_RED, LED_YELOW, LED_ORANGE};
    explicit PerpServer(int nPort);
    ~PerpServer();
    void set_led(uint ledNum, ledColor_t state);

private:
    int port;
    std::array <ledColor_t,5> led_state;
    enum {TYPE_KEEPALIVE, TYPE_SET=2};
    void process_message(int type, int type_specific, int value) override;
    void alive_answer(int type_specific);
    void set_led_state(VgpiClientData * client);
    void signal_new_client(VgpiClientData * client) override;

signals:
    void signal_btn_pressed(int port, int BtnNum);
    void signal_btn_released(int port, int BtnNum);
};

#endif // PERP_SERVER_H
