#ifndef LOGIN_WIDGET_H
#define LOGIN_WIDGET_H

#include <QWidget>
#include "simple_class/user.h"
#include "tool_class/read_data.h"
#include <QMessageBox>

namespace Ui {
class login_widget;
}

class login_widget : public QWidget
{
    Q_OBJECT

public:
    explicit login_widget(QWidget *parent = nullptr);
    ~login_widget();

signals:
    void loginSucceeded(const user &u);

private slots:
    void on_loginbutton_clicked();

private:
    Ui::login_widget *ui;
};

#endif // LOGIN_WIDGET_H
