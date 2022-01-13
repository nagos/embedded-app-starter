#include "snmp_parser.h"
#include <QDebug>

SnmpParser::SnmpCmd SnmpParser::read_cmd(QTextStream * s)
{
    while(!s->atEnd())
    {
        QString str = s->readLine();
        switch(cmdstate){
        case STATE_CMD:
            if(str.compare("PING", Qt::CaseInsensitive) == 0){
                ret_cmd.type = CMD_PING;
                ret_cmd.valid = 1;
                cmdstate = STATE_CMD;
            }else if(str.compare("get", Qt::CaseInsensitive) == 0){
                ret_cmd.type = CMD_GET;
                ret_cmd.valid = 0;
                cmdstate = STATE_ARG1;
            }else if(str.compare("set", Qt::CaseInsensitive) == 0){
                ret_cmd.type = CMD_SET;
                ret_cmd.valid = 0;
                cmdstate = STATE_ARG1;
            }else if(str.compare("getnext", Qt::CaseInsensitive) == 0){
                ret_cmd.type = CMD_GETNEXT;
                ret_cmd.valid = 0;
                cmdstate = STATE_ARG1;
            }
            break;
        case STATE_ARG1:
            ret_cmd.arg1 = str;
            if(ret_cmd.type == CMD_SET){
                cmdstate = STATE_ARG2;
            }else{
                cmdstate = STATE_CMD;
                ret_cmd.valid = 1;
            }
            break;
        case STATE_ARG2:
            ret_cmd.arg2 = str;
            cmdstate = STATE_CMD;
            ret_cmd.valid = 1;
            break;
        };
    }
    return ret_cmd;
}
