#include "writewidget.h"
#include "ui_writewidget.h"

writewidget::writewidget(QWidget *parent, QString site)
    : QWidget(parent)
    , ui(new Ui::writewidget)
{
    ui->setupUi(this);
    this->site = site;
}

writewidget::~writewidget()
{
    delete ui;
}
