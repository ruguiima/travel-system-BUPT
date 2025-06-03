#include "login_widget.h"
#include "ui_login_widget.h"
#include <QScreen>


login_widget::login_widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login_widget)
{
    ui->setupUi(this);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    // 计算窗口的中心位置
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    // 移动窗口到中心位置
    move(x, y);
    this->setWindowTitle("登录界面");
}

login_widget::~login_widget()
{
    delete ui;
}

void login_widget::on_loginbutton_clicked()
{
    QString account = ui->account->toPlainText();
    QString psw = ui->password->toPlainText();
    user u = read_data::getInstance().read_user_data(account);
    if(u.id == 0){
        QMessageBox::warning(this, "账号错误", "请重新输入");
    }
    else if(!u.password.compare(psw.toStdString())){
        QMessageBox::information(this, "登陆成功", "账号密码正确");
        emit loginSucceeded(u);
    }
    else {
        QMessageBox::warning(this, "密码错误", "请重新输入");
    }

}


void login_widget::on_registerbutton_clicked()
{
    register_widget *rw = new register_widget();
    connect(rw, &register_widget::closewidget, this, &login_widget::show);
    rw->show();
}

