#include <QtTest>
#include <QMetaType>
#include "data_storage.h"

typedef struct {
    int a;
    QString b;
} status_input_t;

Q_DECLARE_METATYPE(status_input_t)

class Test_data_storage : public QObject
{
    Q_OBJECT

public:
    Test_data_storage();
    ~Test_data_storage();
    Data_storage data_storage;


private slots:
    void set();
    void get_string();
    void get_int();
    void commit();
    void custom_class();
};


Test_data_storage::Test_data_storage()
{
}


Test_data_storage::~Test_data_storage()
{
}


void Test_data_storage::set()
{
QString key, category_str, key_mix;
QString write_str, read_str;
int write_int, read_int, category_int;

    // Data Initialization
    key = "Test set";
    category_str = "category_str_value";
    category_int = 1;
    write_str = "any text";
    write_int = 1001;

    // Test the text value of the category
    data_storage.set(key, category_str, write_int);
    key_mix = key + category_str;
    read_int = data_storage.get<int>(key_mix);
    QCOMPARE(write_int, read_int);

    read_int = data_storage.get<int>(key, category_str);
    QCOMPARE(write_int, read_int);

    // Test the integer value of the category
    data_storage.set(key, category_int, write_str);
    key_mix = key + QString::number(category_int);
    read_str = data_storage.get<QString>(key_mix);
    QCOMPARE(write_str, read_str);

    read_str = data_storage.get<QString>(key, category_int);
    QCOMPARE(write_str, read_str);
}


void Test_data_storage::get_string()
{
QString key, category_str;
QString write_str, read_str;
int category_int;

    // Data Initialization
    key = "Test get_string";
    category_str = "category_str_value";
    category_int = 2;

    // Test without category
    data_storage.set(key, write_str);
    read_str = data_storage.get<QString>(key);
    QCOMPARE(write_str, read_str);

    // Test the text value of the category
    data_storage.set(key, category_str, write_str);
    read_str = data_storage.get<QString>(key, category_str);
    QCOMPARE(write_str, read_str);

    // Test the integer value of the category
    data_storage.set(key, category_int, write_str);
    read_str = data_storage.get<QString>(key, category_int);
    QCOMPARE(write_str, read_str);
}


void Test_data_storage::get_int()
{
QString key, category_str;
int write_int, read_int, category_int;

    // Data Initialization
    key = "Test get_int";
    category_str = "category_int_value";
    category_int = 2;
    write_int = 1002;

    // Test without category
    data_storage.set(key, write_int);
    read_int = data_storage.get<int>(key);
    QCOMPARE(write_int, read_int);

    // Test the text value of the category
    data_storage.set(key, category_str, write_int);
    read_int = data_storage.get<int>(key, category_str);
    QCOMPARE(write_int, read_int);

    // Test the integer value of the category
    data_storage.set(key, category_int, write_int);
    read_int = data_storage.get<int>(key, category_int);
    QCOMPARE(write_int, read_int);
}


void Test_data_storage::custom_class()
{
    QString key, category_str;

    status_input_t write, read;

    key = "Test get_string";
    category_str = "category_str_value";

    write.a = 1;
    write.b = QString("q");
    data_storage.set(key, category_str, write);
    read = data_storage.get<status_input_t>(key, category_str);

    QCOMPARE(read.a, write.a);
    QCOMPARE(read.b, write.b);
}


void Test_data_storage::commit()
{
QString key, category_str;
int category_int;

    key = "Test get_string";
    category_str = "category_str_value";
    category_int = 1;

    QSignalSpy spy(&data_storage, &Data_storage::signal_data_changed);
    data_storage.commit(key);
    data_storage.commit(key, category_str);
    data_storage.commit(key, category_int);
    QCOMPARE(spy.count(), 3);

    QList<QVariant> arguments;

    arguments = spy.at(0);
    QCOMPARE(arguments.at(0).toString(), key);

    arguments = spy.at(1);
    QCOMPARE(arguments.at(0).toString(), key + category_str);

    arguments = spy.at(2);
    QCOMPARE(arguments.at(0).toString(), key + QString::number(category_int));
}

QTEST_APPLESS_MAIN(Test_data_storage)

#include "test_data_storage.moc"
