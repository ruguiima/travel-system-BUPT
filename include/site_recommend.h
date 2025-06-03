#ifndef SITE_RECOMMEND_H
#define SITE_RECOMMEND_H

#include <QWidget>
#include <QButtonGroup>
#include <QListWidgetItem>
#include <QtSql/QSqlDatabase>
#include <QTableView>
#include <QVBoxLayout>
#include "simple_class/location.h"
#include "tool_class/read_data.h"
#include "kmp_search.h"
#include "top_k_algorithm.h"
#include "tool_class/update_database.h"
#include <sstream>


namespace Ui {
class site_recommend;
}

class site_recommend : public QWidget
{
    Q_OBJECT

public:
    std::vector<location> locations;
    std::vector<location> locationlists;
    std::vector<location> search_site(const std::string str, std::vector<location> locations);

    explicit site_recommend(QWidget *parent = nullptr);
    ~site_recommend();
    void closeEvent(QCloseEvent *event) override;

signals:
    void windowclose();
    void return_to_main_window();

private slots:
    void sort_site();

    void show_location(std::vector<location> locations);

    void on_search_site_button_clicked();

    void on_refresh_button_clicked();

    void on_return_button_clicked();

    void on_next_page_clicked();

    void on_previous_page_clicked();

    void updatePagination(bool keepPage = false);    // 更新分页数据和UI状态

private:
    Ui::site_recommend *ui;
    QButtonGroup *button_group;
    std::vector<location> pagedLocations; // 当前页数据
    int currentPage=0;
    int itemsPerPage=10;
    int getTotalPages() const
    {
        return (locationlists.size() + itemsPerPage - 1) / itemsPerPage;
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // SITE_RECOMMEND_H
