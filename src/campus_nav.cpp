#include "campus_nav.h"
#include "ui_campus_nav.h"

campus_nav::campus_nav(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::campus_nav)
{
    ui->setupUi(this);
}

campus_nav::~campus_nav()
{
    delete ui;
    emit windowclose();
}
