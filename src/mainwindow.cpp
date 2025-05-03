#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(user u, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->u = u;
    ui->welcome->setText("你好，" + QString::fromStdString(u.account));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_diary_widget_clicked()
{
    this->hide();
    diary_window = new diarywindow(u);
    connect(diary_window, &diarywindow::windowclose, this, &MainWindow::show);
    diary_window->show();
}


void MainWindow::on_roadwidget_clicked()
{
    this->hide();
    cam = new campus_nav();
    connect(cam, &campus_nav::windowclose, this, &MainWindow::show);
    cam->show();
}

