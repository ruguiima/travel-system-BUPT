#include "read_data.h"

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
        diarys.push_back(d);
    }
    return diarys;
}

std::vector<location> read_data::read_location_data(){
    std::vector<location> locations;
    QSqlQueryModel model;
    model.setQuery("Select * From Diary");
    for(int i = 0;i < model.rowCount();i++){
        location d;
        d.id = model.record(i).value("id").toInt();
        d.title = model.record(i).value("title").toString().toStdString();
        d.type = model.record(i).value("tyep").toInt();
        d.popularity = model.record(i).value("popularity").toInt();
        d.score = model.record(i).value("score").toFloat();
        d.score_number = model.record(i).value("score_number").toInt();
        d.image_path = model.record(i).value("image_path").toString().toStdString();
        locations.push_back(d);
    }
    return locations;
}
