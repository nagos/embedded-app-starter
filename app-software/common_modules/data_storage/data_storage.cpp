#include "data_storage.h"

Data_storage::Data_storage(QObject *parent) : QObject(parent)
{

}

QString Data_storage::get_key_category(QString key, QString category)
{
    return (key + category);
}

QString Data_storage::get_key_category(QString key, int category)
{
    return (key + QString::number(category));
}

void Data_storage::commit(QString key)
{
    emit signal_data_changed(key);
}
