#include "database_connection.h"
#include <QSettings>
#include <QDir>

database_connection::database_connection() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    QString configPath = QDir::currentPath() + "/config.ini";
    qDebug() << "Config file path:" << configPath;
    QSettings settings(configPath, QSettings::IniFormat);
    QString hostname = settings.value("Database/hostname").toString();
    QString dbname = settings.value("Database/dbname").toString();
    QString username = settings.value("Database/username").toString();
    QString password = settings.value("Database/password").toString();
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
