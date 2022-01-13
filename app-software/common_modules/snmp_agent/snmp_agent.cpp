#include <QLoggingCategory>
#include "snmp_agent.h"

#define DO_RECONNECT_TIME 1000

const SNMP_OID PROFITT_OID = {1, 3, 6, 1, 4, 1, 52035};

static QLoggingCategory category("SNMP_Agent");

const char * Snmp_Agent::SERVER_NAME = "/tmp/sock.unix";

Snmp_Agent::Snmp_Agent()
{
    socket = new QLocalSocket(this);
    in = new QTextStream(socket);
    connect(socket, &QLocalSocket::connected, this, &Snmp_Agent::slot_connected);
    connect(socket, &QLocalSocket::disconnected, this, &Snmp_Agent::slot_disconnected);
    connect(socket, &QLocalSocket::readyRead, this, &Snmp_Agent::slot_readData);
    socket->connectToServer(SERVER_NAME);

    connect(&timer_reconnect, &QTimer::timeout, this, &Snmp_Agent::slot_timer_reconnect);
    timer_reconnect.setInterval(DO_RECONNECT_TIME);
    if(socket->state() == QLocalSocket::UnconnectedState)
        timer_reconnect.start();
}

Snmp_Agent::~Snmp_Agent()
{
    delete in;
    delete socket;
}

void Snmp_Agent::slot_timer_reconnect()
{
    socket->connectToServer(SERVER_NAME);
}

void Snmp_Agent::slot_connected()
{
    timer_reconnect.stop();
}

void Snmp_Agent::slot_disconnected()
{
    timer_reconnect.start();
}

void Snmp_Agent::slot_readData()
{
    QString ret = process.read_cmd(in);
    write_to_socket(ret);
    if(process.set_valid){
        process.set_valid = 0;
        set_val(process.set_oid, mib_value_toInt(process.set_value));
    }
}

void Snmp_Agent::write_to_socket(QString str)
{
    socket->write(str.toLatin1());
}

void Snmp_Agent::set_device_ID(int device_ID)
{
    SNMP_OID oid = PROFITT_OID;
    oid.push_back(device_ID);
    process.set_device_ID(oid);
}

void Snmp_Agent::set_mib_element_int(SNMP_OID key, int value)
{
    process.set_mib_element(key, value);
}

void Snmp_Agent::set_mib_element_str(SNMP_OID key, QString value)
{
    process.set_mib_element(key, value);
}

/* Преобразует строковое значение mib
 * (Managment Information Base) в целое (int)
 */
int Snmp_Agent::mib_value_toInt(QString val)
{
    QStringList StrParted;
    bool ok;

    ok = false;
    StrParted = val.split(' ');
    if(StrParted.size() < 2) return 0;

    if(QString::compare(StrParted[0], "integer", Qt::CaseInsensitive))
        return 0;
    else
        return StrParted.at(1).toInt(&ok, 10);
}
