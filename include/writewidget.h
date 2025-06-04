#ifndef WRITEWIDGET_H
#define WRITEWIDGET_H

#include <QWidget>
#include "simple_class/user.h"
#include "tool_class/update_database.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>

namespace Ui {
class writewidget;
}

// 日记写作窗口类，负责提供用户编写日记的界面和功能
class writewidget : public QWidget
{
    Q_OBJECT // 使得该类可以使用 Qt 的信号与槽机制

public:
    // 构造函数：初始化日记写作窗口，接收用户对象、父窗口指针、地点、地点 ID
    explicit writewidget(user u, QWidget *parent = nullptr, QString site = nullptr, int site_id = 0);

    ~writewidget(); // 析构函数

signals:
    void closewidget(); // 关闭窗口信号

private slots:
    void on_close_clicked(); // 槽函数：处理关闭按钮点击事件

    void on_finisharticle_clicked(); // 槽函数：处理完成文章按钮点击事件

    void on_uploadimage_clicked(); // 槽函数：处理上传图片按钮点击事件

private:
    Ui::writewidget *ui; // 界面元素指针
    QString site; // 当前地点
    user u; // 当前用户对象
    diary d; // 日记对象
};

#endif // WRITEWIDGET_H
