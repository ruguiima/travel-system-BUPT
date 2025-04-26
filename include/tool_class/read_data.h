#ifndef READ_DATA_H
#define READ_DATA_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlRecord>
#include "simple_class/diary.h"
#include "simple_class/location.h"
#include <QtSql/QSqlQuery>
#include "simple_class/user.h"
#include "database_connection.h"
#include <QtSql/QSqlTableModel>
#include <vector>

class read_data
{
public:
    read_data();
    ~read_data();
    static read_data& getInstance();
    std::vector<diary> read_diary_data();
    std::vector<location> read_location_data();
    QString find_diary_sitename(int id);
    user read_user_data(QString account);
    QString find_diary_author(int id);

private:
    QSqlDatabase db;
};

#endif // READ_DATA_H
