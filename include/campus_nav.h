#ifndef CAMPUS_NAV_H
#define CAMPUS_NAV_H

#include <QWidget>
#include "route_plan.h"

namespace Ui {
class campus_nav;
}

class campus_nav : public QWidget
{
    Q_OBJECT

public:
    explicit campus_nav(QWidget *parent = nullptr);
    ~campus_nav();
    void show_nearby(std::vector<place> result);


signals:
    void windowclose();

private slots:
    void on_pushButton_cur_clicked();
    void on_pushButton_search_clicked();
    void on_pushButton_dest_clicked();
    void onDeleteButtonClicked();
    void on_pushButton_plan_clicked();

    void on_pushButton_nearby_clicked();

    void on_pushButton_route_clicked();

private:
    Ui::campus_nav *ui;
    route_plan rp;
    std::unordered_map<QString, int> place_name_to_id;
    int cur_loc = -1;
};

#endif // CAMPUS_NAV_H
