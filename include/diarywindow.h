#ifndef DIARYWINDOW_H
#define DIARYWINDOW_H

#include <QWidget>
#include "location_choose.h"
#include "diaryread.h"
#include <QButtonGroup>
#include "simple_class/user.h"
#include <vector>
#include <QtSql/QSqlDatabase>
#include <QTableView>
#include <QListWidgetItem>
#include "writewidget.h"
#include "./simple_class/diary.h"
#include "./simple_class/location.h"
#include <QVBoxLayout>

namespace Ui {
class diarywindow;
}

class diarywindow : public QWidget
{
    Q_OBJECT

public:
    std::vector<diary> diarys;
    std::vector<location> locations;
    explicit diarywindow(user u, QWidget *parent = nullptr);
    ~diarywindow();
    void show_diary(std::vector<diary> diarys);
    std::vector<diary> search_title(const std::string str, std::vector<diary> diarys);
    std::vector<diary> search_site(const std::string str, std::vector<diary> diarys, std::vector<location> locations);

signals:
    void windowclose();

private slots:
    void on_writediary_clicked();
    void open_write_widget(const QString l, const int id);
    void choose_sort_model();

    void on_sitesearch_clicked();

    void on_titlesearch_clicked();

    void on_diaryslist_itemActivated(QListWidgetItem *item);

private:
    Ui::diarywindow *ui;
    user u;
    QButtonGroup *button_grooup;
    writewidget *write_widget;
    location_choose *location_choose_widget;
};

#endif // DIARYWINDOW_H
