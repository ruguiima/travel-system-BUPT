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
#include "simple_class/user.h"

// 数据库更新类，用于对日记和用户信息进行增删改查
class update_database
{
public:
    update_database(diary d); // 构造函数，接收一个日记对象
    ~update_database();        // 析构函数，关闭数据库连接

    void update_data();        // 更新日记数据
    void insert_data();        // 插入新日记数据
    void change_data();        // 改变数据，如果是新日记则插入，否则更新
    void insert_user_data(user u); // 插入用户数据

private:
    QSqlDatabase db;          // 数据库连接对象
    diary d;                  // 日记对象
};

#endif // UPDATE_DATABASE_H
