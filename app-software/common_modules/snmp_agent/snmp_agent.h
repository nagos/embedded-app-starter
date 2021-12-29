#ifndef SNMP_AGENT_H
#define SNMP_AGENT_H

#include <QObject>
#include <QLocalSocket>
#include <QTimer>

struct oid_object_t {
    QString key;
    QString value;
};

typedef QList<oid_object_t> MIB_t;
typedef QPair<QString, QString> pair_t;
typedef MIB_t::iterator iterator_MIB_t;

class Snmp_Agent : public QObject
{
    Q_OBJECT
public:
    explicit Snmp_Agent();

    void set_device_ID(int device_ID);
    void set_mib_element_int(QString key, int value);
    void set_mib_element_int32(QString key,  qint32 value);
    void set_mib_element_str(QString key, QString str);
    QString get_oid_element(QString key);

private:
    QLocalSocket *socket;
    QTimer timer_reconnect;
    int cmd_type;
    QString OID_node, OID_node_dot;
    MIB_t MIB_map;
    oid_object_t oid_object;
    QTextStream * in;
    static const char * SERVER_NAME;
    iterator_MIB_t iterator_to_set;

    void parse_datagram(QString str);
    void parse_command(QString str);
    void write_to_socket(QString str);
    void cmd_get(QString str);
    void cmd_set(QString str);
    void cmd_get_next(QString str);
    bool device_node(QString str);
    void MIB_map_append(QString key, QString value);
    auto find_index(QString key) {
        return std::find_if(MIB_map.begin(), MIB_map.end(), 
            [=](oid_object_t elm){return elm.key.compare(key, Qt::CaseInsensitive) == 0;}
        );
    };
    auto get_index(QString key){
        key.remove(OID_node_dot);
        return find_index(key);
    };


protected:
    virtual void set_val(QString key, QString val){};

public slots:

    void slot_connected();
    void slot_disconnected();
    void slot_readData();
    void slot_timer_reconnect();
};

#endif // SNMP_AGENT_H
