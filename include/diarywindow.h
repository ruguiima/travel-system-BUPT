#ifndef DIARYWINDOW_H
#define DIARYWINDOW_H

#include "tool_class/HuffmanCoding.h"
#include <QWidget>
#include "location_choose.h"
#include "diaryread.h"
#include <QButtonGroup>
#include "simple_class/user.h"
#include "top_k_algorithm.h"
#include <vector>
#include <QtSql/QSqlDatabase>
#include <QTableView>
#include <QListWidgetItem>
#include "writewidget.h"
#include "simple_class/diary.h"
#include "simple_class/location.h"
#include <QVBoxLayout>

namespace Ui {
class diarywindow;
}

// 日记窗口类，负责日记的显示、管理和用户交互
class diarywindow : public QWidget
{
    Q_OBJECT // 使得该类可以使用 Qt 的信号与槽机制

public:
    std::vector<diary> diarys; // 存储所有日记的 vector
    std::vector<diary> diarylist; // 可搜索的日记列表
    std::vector<location> locations; // 地点列表

    // 构造函数：初始化日记窗口，接收用户对象
    explicit diarywindow(user u, QWidget *parent = nullptr);

    // 构造函数：初始化日记窗口，接收用户对象和搜索内容
    explicit diarywindow(user u, QString search_content, QWidget *parent = nullptr);

    ~diarywindow(); // 析构函数

    // 显示日记列表
    void show_diary(std::vector<diary> diarys);

    // 根据标题搜索日记
    std::vector<diary> search_title(const std::string str, std::vector<diary> diarys);

    // 根据地点搜索日记
    std::vector<diary> search_site(const std::string str, std::vector<diary> diarys, std::vector<location> locations);

    // 处理窗口关闭事件
    void closeEvent(QCloseEvent *event) override;

    // 更新分页显示
    void updatePagination(bool keepPage = false);

signals:
    void windowclose(); // 窗口关闭信号
    void open_local_file(); // 打开本地文件信号

private slots:
    void on_writediary_clicked(); // 槽函数：处理写日记按钮点击事件
    void open_write_widget(const QString l, const int id); // 打开写日记窗口
    void choose_sort_model(); // 选择排序模型

    // 槽函数：处理地点搜索按钮点击事件
    void on_sitesearch_clicked();

    // 槽函数：处理标题搜索按钮点击事件
    void on_titlesearch_clicked();

    // 槽函数：处理日记列表项激活事件
    void on_diaryslist_itemActivated(QListWidgetItem *item);

    // 槽函数：处理刷新按钮点击事件
    void on_refresh_clicked();

    // 槽函数：处理加载本地日记按钮点击事件
    void on_load_local_diary_clicked();

    // 槽函数：处理下一页按钮点击事件
    void on_next_page_clicked();

    // 槽函数：处理上一页按钮点击事件
    void on_previous_page_clicked();

private:
    Ui::diarywindow *ui; // 界面元素指针
    user u; // 当前用户对象
    QButtonGroup *button_grooup; // 按钮组
    writewidget *write_widget; // 写日记窗口指针
    location_choose *location_choose_widget; // 地点选择窗口指针
    bool keepPage; // 是否保持当前分页状态
    int currentPage = 0; // 当前页码
    int itemsPerPage = 10; // 每页显示的日记项数
    std::vector<diary> pagedDiarys; // 当前页数据

    // 计算总页数
    int getTotalPages() const
    {
        return (diarylist.size() + itemsPerPage - 1) / itemsPerPage; // 向上取整计算总页数
    }
};

#endif // DIARYWINDOW_H
