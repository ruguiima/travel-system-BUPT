#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

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

void MainWindow::on_sitewidget_clicked()
{
    this->hide();
    site =new site_recommend(u);
    connect(site, &site_recommend::windowclose,this,&MainWindow::show);
    connect(site, &site_recommend::return_to_main_window, this, &MainWindow::show);
    site->show();
}


void MainWindow::on_exitbutton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "退出确认", "感谢您的使用！您确定要退出吗？",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit(); // 退出应用程序
    }
}

