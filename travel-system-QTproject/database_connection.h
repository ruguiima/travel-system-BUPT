#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H
#include <QtSql/QSqlDatabase>
#include <QString>
class database_connection
{
public:
    static database_connection& getInstance();    //获取数据库对象的单实例
    bool connect();
    void disconnect();
    QSqlDatabase get_data_base();
    database_connection();
    ~database_connection();

private:
    QSqlDatabase db;
    QString hostname;
    QString dbname;
    QString username;
    QString password;
};

#endif // DATABASE_CONNECTION_H
