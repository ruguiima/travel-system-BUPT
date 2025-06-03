#include "register_widget.h"
#include "ui_register_widget.h"
#include <QMessageBox>
register_widget::register_widget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::register_widget)
{
    ui->setupUi(this);
}

register_widget::~register_widget()
{
    delete ui;
}


void register_widget::on_buttonBox_rejected()
{
    emit closewidget();
    register_widget::~register_widget();
}


void register_widget::on_buttonBox_accepted()
{
    this->u.account = ui->accountinput->toPlainText().toStdString();
    this->u.password = ui->passwordinput->toPlainText().toStdString();
    diary d;
    update_database ud(d);
    ud.insert_user_data(this->u);
    QMessageBox::StandardButton reply = QMessageBox::question(this, "确认", "信息是否正确",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit closewidget();
        this->hide();
        register_widget::~register_widget();
    }
}

