#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include <QObject>
#include <QVariant>
#include <QHash>

class Data_storage : public QObject
{
    Q_OBJECT
public:
    explicit Data_storage(QObject *parent = nullptr);

    template <typename V> void set(QString key, V value){
        data_container[key] = QVariant::fromValue(value);
    }

    template <typename C, typename V> void set(QString key, C category, V value){
        QString k = get_key_category(key, category);
        set(k, value);
    }

    template <typename T, typename C=QString> T get(QString key, C category=QString("")){
        QString k = get_key_category(key, category);
        Q_ASSERT_X(data_container.contains(k), "Specified key does not exist", qUtf8Printable(k));
        return data_container[k].value<T>();
    };

    void     commit(QString key);
    template <typename C=QString>  void commit(QString key, C category){
        QString k = get_key_category(key, category);
        commit(k);
    };

private:
    QHash<QString, QVariant>  data_container;
    QString get_key_category(QString key, QString category);
    QString get_key_category(QString key, int category);

signals:
    void signal_data_changed(QString data_name);

};

#endif // DATA_STORAGE_H
