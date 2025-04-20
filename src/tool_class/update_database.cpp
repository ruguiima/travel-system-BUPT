#include "tool_class/update_database.h"

update_database::update_database(diary d) {
    this->d = d;
    db = database_connection::getInstance().get_data_base();
    if(!db.isOpen())
        db.open();
}

update_database::~update_database(){
    if(db.isOpen())
        db.close();
}

void update_database::change_data()
{
    if(d.id == -1)
        this->insert_data();
    else
        this->update_data();
}

void update_database::update_data()
{
    qDebug() << "正在修改信息";
    QSqlTableModel model;
    model.setTable("Diary");
    model.setFilter("id = " + QString::number(d.id));
    model.select();
    QSqlRecord record = model.record(0);
    qDebug() << QString::fromStdString(d.title);
    record.setValue("score_number", d.score_number);
    record.setValue("score", d.score);
    record.setValue("popularity", d.popularity);
    model.setRecord(0, record); // 确保模型更新记录
    if (!model.submitAll()) {
        qDebug() << "提交失败：" << model.lastError().text();
    } else {
        qDebug() << "信息更新成功";
    }
}

void update_database::insert_data()
{
    QSqlTableModel model;
    model.setTable("Diary");
    model.select();
    QSqlRecord record = model.record();
    record.setValue("author", d.author);
    record.setValue("site_id", d.site_id);
    record.setValue("context", QString::fromStdString(d.context));
    record.setValue("score", 0);
    record.setValue("score_number", 0);
    record.setValue("popularity", 0);
    record.setValue("image_path", QString::fromStdString(d.image_path));
    record.setValue("title", QString::fromStdString(d.title));
    model.insertRecord(-1, record);
    model.submitAll();
}
