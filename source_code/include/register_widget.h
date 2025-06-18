#ifndef REGISTER_WIDGET_H
#define REGISTER_WIDGET_H

#include <QDialog>
#include "./include/simple_class/user.h"
#include "./include/tool_class/update_database.h"

namespace Ui {
class register_widget;
}

// 注册窗口类，负责用户注册的界面和功能
class register_widget : public QDialog
{
    Q_OBJECT // 使得该类可以使用 Qt 的信号与槽机制

public:
    // 构造函数，初始化注册窗口
    explicit register_widget(QWidget *parent = nullptr);
    ~register_widget(); // 析构函数

signals:
    void closewidget(); // 关闭窗口信号

private slots:
    void on_buttonBox_rejected(); // 槽函数：处理取消按钮点击事件
    void on_buttonBox_accepted(); // 槽函数：处理确认按钮点击事件

private:
    Ui::register_widget *ui; // 界面元素指针
    user u;                  // 用户对象
};

#endif // REGISTER_WIDGET_H
