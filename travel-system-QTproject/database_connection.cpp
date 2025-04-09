#include "database_connection.h"

database_connection::database_connection() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    hostname = "123.56.154.190"; // 数据库主机名
    dbname = "travel-system"; // 数据库名称
    username = "travel-system-database";   // 数据库用户名
    password = "Q2SWraFR3zKAP3bD"; // 数据库密码
    db.setHostName(hostname); // 设置主机名
    db.setDatabaseName(dbname); // 设置数据库名称
    db.setUserName(username); // 设置用户名
    db.setPassword(password); // 设置密码
}

database_connection::~database_connection(){
    disconnect();
}

database_connection& database_connection::getInstance(){
    static database_connection instance;
    return instance;
}

bool database_connection::connect(){
    if(!db.open()){
        qDebug()  << "数据库连接失败";
        return false;
    }
    return true;
}

void database_connection::disconnect(){
    if(db.isOpen()){
        db.close();
    }
}

QSqlDatabase database_connection::get_data_base(){
    return db;
}
