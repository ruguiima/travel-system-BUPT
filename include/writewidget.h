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

class writewidget : public QWidget
{
    Q_OBJECT

public:
    explicit writewidget(user u, QWidget *parent = nullptr, QString site = nullptr, int site_id = 0);
    ~writewidget();

signals:
    void closewidget();
private slots:
    void on_close_clicked();

    void on_finisharticle_clicked();

    void on_uploadimage_clicked();

private:
    Ui::writewidget *ui;
    QString site;
    user u;
    diary d;
};

#endif // WRITEWIDGET_H
