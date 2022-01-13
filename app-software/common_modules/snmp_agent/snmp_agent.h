#ifndef SNMP_AGENT_H
#define SNMP_AGENT_H

#include <QObject>
#include <QLocalSocket>
#include <QTimer>
#include "snmp_process.h"

class Snmp_Agent : public QObject
{
    Q_OBJECT
public:
    enum CMD_TYPE {CMD_PING, CMD_GET, CMD_SET, CMD_GET_NEXT};
    explicit Snmp_Agent();
    ~Snmp_Agent();

    void set_device_ID(int device_ID);
    void set_mib_element_int(SNMP_OID key, int value);
    void set_mib_element_str(SNMP_OID key, QString value);
    static int mib_value_toInt(QString val);

private:
    QLocalSocket *socket;
    QTimer timer_reconnect;
    QTextStream * in;
    static const char * SERVER_NAME;
    SnmpProcess process;

    void write_to_socket(QString str);

protected:
    virtual void set_val(SNMP_OID key, QVariant val){};

private slots:

    void slot_connected();
    void slot_disconnected();
    void slot_readData();
    void slot_timer_reconnect();
};

#endif // SNMP_AGENT_H
