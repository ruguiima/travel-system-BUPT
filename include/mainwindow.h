#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "diarywindow.h"
#include "campus_nav.h"

#include "site_recommend.h"

#include "simple_class/user.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow; // 前向声明 MainWindow 界面类
}
QT_END_NAMESPACE

// 主窗口类，负责应用程序的主界面及其交互
class MainWindow : public QMainWindow
{
    Q_OBJECT // 使得该类可以使用 Qt 的信号与槽机制

public:
    // 构造函数，接收用户对象和父窗口指针
    MainWindow(user u, QWidget *parent = nullptr);
    ~MainWindow(); // 析构函数

private slots:
    // 槽函数：日记小组件被点击时的响应
    void on_diary_widget_clicked();

    // 槽函数：校园路线小组件被点击时的响应
    void on_roadwidget_clicked();

    // 槽函数：景点小组件被点击时的响应
    void on_sitewidget_clicked();

    // 槽函数：退出按钮被点击时的响应
    void on_exitbutton_clicked();

private:
    Ui::MainWindow *ui; // 界面元素指针
    user u;             // 当前用户对象
    diarywindow *diary_window; // 日记窗口指针
    campus_nav *cam;    // 校园导航指针
    site_recommend *site; // 景点推荐指针
};

#endif // MAINWINDOW_H
