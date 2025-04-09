#ifndef DIARYWINDOW_H
#define DIARYWINDOW_H

#include <QWidget>
#include <QButtonGroup>
#include <vector>
#include <QtSql/QSqlDatabase>
#include <QTableView>
#include "writewidget.h"
#include "./simple_class/diary.h"
#include "./simple_class/location.h"

namespace Ui {
class diarywindow;
}

class diarywindow : public QWidget
{
    Q_OBJECT

public:
    explicit diarywindow(QWidget *parent = nullptr);
    ~diarywindow();
    void show_diary();

private slots:
    void on_writediary_clicked();

private:
    Ui::diarywindow *ui;
    QButtonGroup *button_grooup;
    writewidget *write_widget;
    std::vector<diary> diarys;
    std::vector<location> locations;
};

#endif // DIARYWINDOW_H
