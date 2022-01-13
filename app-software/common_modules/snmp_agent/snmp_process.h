#if !defined(SNMP_PROCESS_H)
#define SNMP_PROCESS_H

#include <QObject>
#include "snmp_parser.h"

using SNMP_OID = std::vector<int>;

class SnmpProcess : public QObject
{
    Q_OBJECT
public:
    struct SnmpSet {
        QString key;
        QString value;
        int valid;
        SnmpSet():
            key(QString()),
            value(QString()),
            valid(0)
        {};
    };
    SNMP_OID set_oid;
    QString set_value;
    int set_valid;
    explicit SnmpProcess(): set_valid(0) {};
    QString read_cmd(QTextStream * s);
    static SNMP_OID oid_to_vector(QString s);
    QString vector_to_oid(SNMP_OID v);
    void set_device_ID(SNMP_OID oid);
    void set_mib_element(SNMP_OID oid, int v);
    void set_mib_element(SNMP_OID oid, QString v);
private:
    SnmpParser parser;
    SNMP_OID device_oid;
    std::map<SNMP_OID,QString> storage;
    QString cmd_ping(SnmpParser::SnmpCmd cmd);
    QString cmd_get(SnmpParser::SnmpCmd cmd);
    QString cmd_get(SNMP_OID oid);
    QString cmd_getnext(SnmpParser::SnmpCmd cmd);
    QString cmd_set(SnmpParser::SnmpCmd cmd);
    void set_mib_element_raw(SNMP_OID oid, QString v);
};


#endif // SNMP_PROCESS_H
