    #include "writewidget.h"
#include "ui_writewidget.h"

writewidget::writewidget(QWidget *parent, QString site)
    : QWidget(parent)
    , ui(new Ui::writewidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    this->site = site;
    ui->location_title->setText(site);
}

writewidget::~writewidget()
{
    emit writewidget::closewidget();
    delete ui;
}

void writewidget::on_close_clicked()
{
    writewidget::~writewidget();
}
