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
    std::vector<diary> diarys;
    QSqlQueryModel model;
    model.setQuery("Select * From Diary");
    for(int i = 0;i < model.rowCount();i++){
        diary d;
        d.id = model.record(i).value("id").toInt();
        d.title = model.record(i).value("title").toString().toStdString();
        d.context = model.record(i).value("context").toString().toStdString();
        d.site_id = model.record(i).value("site_id").toInt();
        d.author = model.record(i).value("author").toInt();
        d.popularity = model.record(i).value("popularity").toInt();
        d.score = model.record(i).value("score").toFloat();
        d.score_number = model.record(i).value("score_number").toInt();
        d.image_path = model.record(i).value("image_path").toString().toStdString();
        if(d.author == 0)
            d.author_name = "佚名";
        diarys.push_back(d);
    }
    return diarys;
}

std::vector<location> read_data::read_location_data(){
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
