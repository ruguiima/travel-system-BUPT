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

// 数据读取类，用于从数据库中读取各种类型的数据
class read_data
{
public:
    read_data();                                           // 构造函数，初始化数据库连接
    ~read_data();                                          // 析构函数，关闭数据库连接
    static read_data& getInstance();                       // 获取单例实例

    std::vector<diary> read_diary_data();                 // 读取日记数据
    std::vector<location> read_location_data();           // 读取地点数据
    QString find_diary_sitename(int id);                  // 根据 ID 查找日记的地点名称
    user read_user_data(QString account);                  // 根据账号查找用户数据
    QString find_diary_author(int id);                     // 根据 ID 查找日记的作者

private:
    QSqlDatabase db;                                       // 数据库连接对象
};

#endif // READ_DATA_H
