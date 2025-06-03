#ifndef REGISTER_WIDGET_H
#define REGISTER_WIDGET_H

#include <QDialog>
#include "./include/simple_class/user.h"
#include "./include/tool_class/update_database.h"

namespace Ui {
class register_widget;
}

class register_widget : public QDialog
{
    Q_OBJECT

public:
    explicit register_widget(QWidget *parent = nullptr);
    ~register_widget();

signals:
    void closewidget();
private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::register_widget *ui;
    user u;
};

#endif // REGISTER_WIDGET_H
