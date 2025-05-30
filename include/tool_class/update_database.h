#ifndef UPDATE_DATABASE_H
#define UPDATE_DATABASE_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include "simple_class/diary.h"
#include "database_connection.h"

class update_database
{
public:
    update_database(diary d);
    ~update_database();
    void update_data();
    void insert_data();
    void change_data();

private:
    QSqlDatabase db;
    diary d;
};

#endif // UPDATE_DATABASE_H
