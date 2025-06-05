#ifndef LOGIN_WIDGET_H
#define LOGIN_WIDGET_H

#include <QWidget>
#include "simple_class/user.h"
#include "tool_class/read_data.h"
#include <QMessageBox>
#include "register_widget.h"

namespace Ui {
class login_widget; // 前向声明 login_widget 界面类
}

// 登录窗口类，负责用户登录界面的功能和交互
class login_widget : public QWidget
{
    Q_OBJECT // 使得该类可以使用 Qt 的信号与槽机制

public:
    // 构造函数，初始化登录窗口
    explicit login_widget(QWidget *parent = nullptr);
    ~login_widget(); // 析构函数

signals:
    void loginSucceeded(const user &u); // 登录成功信号，传递用户信息

private slots:
    void on_loginbutton_clicked(); // 槽函数：处理登录按钮点击事件
    void on_registerbutton_clicked(); // 槽函数：处理注册按钮点击事件

private:
    Ui::login_widget *ui; // 界面元素指针
};

#endif // LOGIN_WIDGET_H
