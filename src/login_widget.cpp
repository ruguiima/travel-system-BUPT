#include "login_widget.h"
#include "ui_login_widget.h"

login_widget::login_widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login_widget)
{
    ui->setupUi(this);
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

