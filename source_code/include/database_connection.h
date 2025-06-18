#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H
#include <QtSql/QSqlDatabase>
#include <QString>

// 数据库连接类，负责管理与数据库的连接
class database_connection
{
public:
    static database_connection& getInstance(); // 获取数据库对象的单例实例
    bool connect();       // 连接到数据库
    void disconnect();    // 断开与数据库的连接
    QSqlDatabase get_data_base(); // 获取 QSqlDatabase 对象

    database_connection(); // 构造函数，初始化数据库参数
    ~database_connection(); // 析构函数，确保断开连接

private:
    QSqlDatabase db;      // 数据库连接对象
    QString hostname;     // 数据库主机名
    QString dbname;       // 数据库名称
    QString username;     // 数据库用户名
    QString password;     // 数据库密码
};


#endif // DATABASE_CONNECTION_H
