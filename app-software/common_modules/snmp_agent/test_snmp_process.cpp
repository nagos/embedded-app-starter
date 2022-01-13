#include <QtTest>
#include "snmp_process.h"

class Test_snmp_process : public QObject
{
    Q_OBJECT
public:
    Test_snmp_process(){};
    ~Test_snmp_process(){};
private slots:
    void test_ping(){
        SnmpProcess process;
        QTextStream data1("PING\n");
        QString ret = process.read_cmd(&data1);
        QCOMPARE(ret, "PONG\n");
    };
    void test_get(){
        SnmpProcess process;
        process.set_device_ID({1, 3, 6, 1, 4, 1, 52035, 19});
        process.set_mib_element({3}, 1);
        process.set_mib_element({4}, QString("test"));

        QTextStream data1("get\n.1.3.6.1.4.1.52035.19.3\n");
        QString ret = process.read_cmd(&data1);
        QCOMPARE(ret, QString(".1.3.6.1.4.1.52035.19.3\nINTEGER\n1\n"));

        QTextStream data2("get\n.1.3.6.1.4.1.52035.19.4\n");
        QString ret_str = process.read_cmd(&data2);
        QCOMPARE(ret_str, QString(".1.3.6.1.4.1.52035.19.4\nstring\ntest\n"));
        
    };
    void test_set(){
        SnmpProcess process;
        process.set_device_ID({1, 3, 6, 1, 4, 1, 52035, 19});
        process.set_mib_element({3}, 1);

        QTextStream data1("set\n.1.3.6.1.4.1.52035.19.3\ninteger 1\n");
        QString ret = process.read_cmd(&data1);
        QCOMPARE(ret, QString("OK\n"));

    };
    void test_getnext(){
        SnmpProcess process;
        process.set_device_ID({1, 3, 6, 1, 4, 1, 52035, 19});
        process.set_mib_element({3}, 1);
        process.set_mib_element({4}, QString("test"));

        QString ret;
        QTextStream data1("getnext\n.1.3.6.1.4.1.52035.19.3\n");
        ret = process.read_cmd(&data1);
        QCOMPARE(ret, ".1.3.6.1.4.1.52035.19.4\nstring\ntest\n");

        QTextStream data2("getnext\n.1.3.6.1.4.1.52035.19.4\n");
        ret = process.read_cmd(&data2);
        QCOMPARE(ret, "none\n");

        QTextStream data3("getnext\n.1.3.6.1.4.1.52035.19\n");
        ret = process.read_cmd(&data3);
        QCOMPARE(ret, ".1.3.6.1.4.1.52035.19.3\nINTEGER\n1\n");

    };
    void test_oid_to_vector(){
        std::vector<int> v = SnmpProcess::oid_to_vector(".1.3.6.1.4.1.52035.19.3");
        std::vector<int> r = {1, 3, 6, 1, 4, 1, 52035, 19, 3};
        QCOMPARE(v, r);
    };
};

QTEST_APPLESS_MAIN(Test_snmp_process)

#include "test_snmp_process.moc"
