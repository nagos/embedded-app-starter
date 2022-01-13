#if !defined(SNMP_PARSER_H)
#define SNMP_PARSER_H

#include <QObject>
#include <QTextStream>
#include <string>

class SnmpParser : public QObject
{
    Q_OBJECT
public:
    enum CmdType {CMD_PING, CMD_GET, CMD_GETNEXT, CMD_SET, CMD_NONE};
    struct SnmpCmd {
        CmdType type;
        QString arg1;
        QString arg2;
        int valid;
        SnmpCmd():
            type(CMD_NONE),
            valid(0)
        {};
        operator QString() const { return QString("%1,%2,%3,%4").arg(type).arg(arg1).arg(arg2).arg(valid); };
    };
    explicit SnmpParser():
        cmdstate(STATE_CMD)
    {};
    SnmpCmd read_cmd(QTextStream * s);
private:
    enum CmdState {STATE_CMD, STATE_ARG1, STATE_ARG2};
    CmdState cmdstate;
    SnmpCmd ret_cmd;
};


#endif // SNMP_PARSER_H
