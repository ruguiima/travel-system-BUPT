#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(user u, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->u = u;
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

