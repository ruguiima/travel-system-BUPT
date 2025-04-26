#include "tool_class/read_data.h"

read_data::read_data() {
    db = database_connection::getInstance().get_data_base();
    db.open();
}

read_data::~read_data(){
    db.close();
}

read_data& read_data::getInstance(){
    static read_data rd;
    return rd;
}

std::vector<diary> read_data::read_diary_data(){
    if(!db.isOpen())
        db.open();
    std::vector<diary> diarys;
    QSqlQuery query;
    query.exec("SELECT d.*, u.account AS author_name, l.name AS site_name "
               "FROM Diary d "
               "LEFT JOIN User u ON d.author = u.id "
               "LEFT JOIN Location l ON d.site_id = l.id");

    while (query.next()) {
        diary d;
        d.id = query.value("id").toInt();
        d.title = query.value("title").toString().toStdString();
        d.context = query.value("context").toString().toStdString();
        d.site_id = query.value("site_id").toInt();
        d.site_name = query.value("site_name").toString().toStdString(); // 直接从查询获得
        d.author = query.value("author").toInt();
        d.popularity = query.value("popularity").toInt();
        d.score = query.value("score").toFloat();
        d.score_number = query.value("score_number").toInt();
        d.image_path = query.value("image_path").toString().toStdString();
        d.author_name = query.value("author_name").toString().toStdString(); // 直接从查询获得

        diarys.push_back(d);
    }
    return diarys;
}
std::vector<location> read_data::read_location_data(){
    if(!db.isOpen())
        db.open();
    std::vector<location> locations;
    QSqlQueryModel model;
    model.setQuery("Select * From Location");
    for(int i = 0;i < model.rowCount();i++){
        location d;
        d.id = model.record(i).value("id").toInt();
        d.title = model.record(i).value("name").toString().toStdString();
        // qDebug() << d.title;
        d.type = model.record(i).value("type").toInt();
        d.popularity = model.record(i).value("popularity").toInt();
        d.score = model.record(i).value("score").toFloat();
        d.score_number = model.record(i).value("score_number").toInt();
        locations.push_back(d);
    }
    return locations;
}

user read_data::read_user_data(QString account){
    if(!db.isOpen())
        db.open();
    user u;
    QSqlTableModel model;
    model.setTable("User");
    model.setFilter(QString("account = '%1'").arg(account));
    model.select();
    if(model.rowCount() == 0){
        qDebug() << "未搜到用户";
        u.id = 0;
        return u;
    }
    qDebug() << "搜到用户";
    QSqlRecord record = model.record(0);
    u.id = record.value("id").toInt();
    u.account = record.value("account").toString().toStdString();
    u.password = record.value("password").toString().toStdString();
    return u;
}
