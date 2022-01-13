#include "snmp_process.h"
#include <QDebug>

QString SnmpProcess::cmd_ping(SnmpParser::SnmpCmd cmd)
{
    return "PONG\n";
}

QString SnmpProcess::cmd_get(SnmpParser::SnmpCmd cmd)
{
    auto oid = oid_to_vector(cmd.arg1);
    return cmd_get(oid);
}

QString SnmpProcess::cmd_get(SNMP_OID oid)
{
    auto e = storage.find(oid);
    if(e==storage.end())
        return "none\n";
    else
        return QString("%1\n%2").arg(vector_to_oid(e->first)).arg(e->second);
}

QString SnmpProcess::cmd_set(SnmpParser::SnmpCmd cmd)
{
    return "OK\n";
}

QString SnmpProcess::cmd_getnext(SnmpParser::SnmpCmd cmd)
{
    auto oid = oid_to_vector(cmd.arg1);
    auto e = storage.find(oid);

    if(oid<storage.begin()->first)
        return cmd_get(storage.begin()->first);
    if(e==storage.end())
        return "none\n";
    ++e;
    if(e==storage.end())
        return "none\n";
    return cmd_get(e->first);
}

QString SnmpProcess::read_cmd(QTextStream * s)
{
    QString ret;
    SnmpParser::SnmpCmd cmd = parser.read_cmd(s);
    if(cmd.valid){
        set_valid = 0;
        switch(cmd.type){
        case SnmpParser::CMD_PING:
            ret = cmd_ping(cmd);
            break;
        case SnmpParser::CMD_GET:
            ret = cmd_get(cmd);
            break;
        case SnmpParser::CMD_GETNEXT:
            ret = cmd_getnext(cmd);
            break;
        case SnmpParser::CMD_SET:
            ret = cmd_set(cmd);
            set_oid = oid_to_vector(cmd.arg1);
            set_oid.erase(set_oid.begin(), set_oid.begin() + device_oid.size());
            set_value = cmd.arg2;
            set_valid = 1;
            break;
        }
    }
    return ret;
}

SNMP_OID SnmpProcess::oid_to_vector(QString s)
{
    SNMP_OID ret;

    QStringList list = s.split(QLatin1Char('.'));
    for(QString i: list){
        if(i!="")
            ret.push_back(i.toInt());
    }
    return ret;
}

QString SnmpProcess::vector_to_oid(SNMP_OID v)
{
    QString ret;

    for(int i: v)
        ret += QString(".%1").arg(i);
    return ret;
}

void SnmpProcess::set_device_ID(SNMP_OID oid)
{
    device_oid = oid;
}

void SnmpProcess::set_mib_element(SNMP_OID oid, int v)
{
    set_mib_element_raw(oid, QString("INTEGER\n%1\n").arg(v));
}

void SnmpProcess::set_mib_element(SNMP_OID oid, QString v)
{
    set_mib_element_raw(oid, QString("string\n%1\n").arg(v));
}

void SnmpProcess::set_mib_element_raw(SNMP_OID oid, QString v)
{
    oid.insert(oid.begin(), device_oid.begin(), device_oid.end());
    storage[oid] = v;
}
