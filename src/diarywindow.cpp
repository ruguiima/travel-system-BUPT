#include "diarywindow.h"
#include "ui_diarywindow.h"
#include "tool_class/read_data.h"

diarywindow::diarywindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::diarywindow),write_widget()
{
    ui->setupUi(this);
    button_grooup = new QButtonGroup(this);
    button_grooup->addButton(ui->scoreorder);
    button_grooup->addButton(ui->popularityorder);
    button_grooup->setExclusive(true);
    diarys = read_data::getInstance().read_diary_data();
    locations = read_data::getInstance().read_location_data();
    show_diary();
}

diarywindow::~diarywindow()
{
    delete ui;
}

void diarywindow::on_writediary_clicked()
{
    write_widget = new writewidget(nullptr, "hehe");
    write_widget->show();
}

void diarywindow::show_diary(){

}

