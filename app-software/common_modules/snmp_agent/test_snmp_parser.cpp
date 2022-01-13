#include <QtTest>
#include <map>
#include <vector>
#include "snmp_parser.h"

class Test_snmp : public QObject
{
    Q_OBJECT
public:
    Test_snmp(){};
    ~Test_snmp(){};
private slots:
    void test_ping(){
        SnmpParser parser;
        QTextStream data1("PING\n");
        SnmpParser::SnmpCmd cmd1 = parser.read_cmd(&data1);
        QCOMPARE(cmd1.valid, 1);
        QCOMPARE(cmd1.type, SnmpParser::CMD_PING);
    };
    void test_get(){
        SnmpParser parser;
        QTextStream data1("get\n");
        QTextStream data2(".1.3.6.1.4.1.52035.19.3\n");
        SnmpParser::SnmpCmd cmd1 = parser.read_cmd(&data1);
        SnmpParser::SnmpCmd cmd2 = parser.read_cmd(&data2);
        QCOMPARE(cmd1.valid, 0);
        QCOMPARE(cmd2.valid, 1);
        QCOMPARE(cmd2.type, SnmpParser::CMD_GET);
    };
    void test_set(){
        SnmpParser parser;
        QTextStream data1("set\n");
        QTextStream data2(".1.3.6.1.4.1.52035.19.3\n");
        QTextStream data3("integer 0\n");
        SnmpParser::SnmpCmd cmd1 = parser.read_cmd(&data1);
        SnmpParser::SnmpCmd cmd2 = parser.read_cmd(&data2);
        SnmpParser::SnmpCmd cmd3 = parser.read_cmd(&data3);
        QCOMPARE(cmd1.valid, 0);
        QCOMPARE(cmd2.valid, 0);
        QCOMPARE(cmd3.valid, 1);
        QCOMPARE(cmd3.type, SnmpParser::CMD_SET);
        QCOMPARE(cmd3.arg1, QString(".1.3.6.1.4.1.52035.19.3"));
    };
    void test_getnext(){
        SnmpParser parser;
        QTextStream data1("getnext\n");
        QTextStream data2(".1.3.6.1.4.1.52035.19.4\n");
        SnmpParser::SnmpCmd cmd1 = parser.read_cmd(&data1);
        SnmpParser::SnmpCmd cmd2 = parser.read_cmd(&data2);
        QCOMPARE(cmd1.valid, 0);
        QCOMPARE(cmd2.valid, 1);
        QCOMPARE(cmd2.type, SnmpParser::CMD_GETNEXT);
        QCOMPARE(cmd2.arg1, QString(".1.3.6.1.4.1.52035.19.4"));
    };
    void test_getnext_combined(){
        SnmpParser parser;
        QTextStream data1("getnext\n.1.3.6.1.4.1.52035.19.5\n");
        SnmpParser::SnmpCmd cmd1 = parser.read_cmd(&data1);
        QCOMPARE(cmd1.valid, 1);
        QCOMPARE(cmd1.type, SnmpParser::CMD_GETNEXT);
        QCOMPARE(cmd1.arg1, QString(".1.3.6.1.4.1.52035.19.5"));
    };
};


QTEST_APPLESS_MAIN(Test_snmp)

#include "test_snmp_parser.moc"
