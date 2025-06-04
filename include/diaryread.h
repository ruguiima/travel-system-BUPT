#ifndef DIARYREAD_H
#define DIARYREAD_H

#include <QWidget>
#include "simple_class/diary.h"
#include <QButtonGroup>
#include "tool_class/update_database.h"
#include "tool_class/HuffmanCoding.h"
#include <QPixmap>

namespace Ui {
class diaryread;
}

// 日记阅读窗口类，负责显示单条日记的内容以及用户交互
class diaryread : public QWidget
{
    Q_OBJECT // 使得该类可以使用 Qt 的信号与槽机制

public:
    // 构造函数：初始化日记阅读窗口，接收日记信息和父窗口指针
    explicit diaryread(diary info, QWidget *parent = nullptr);

    // 更新数据库中的日记信息
    void diary_data_change();

    // 更新日记评分
    void diary_score_change(int number);

    // 处理窗口关闭事件
    void closeEvent(QCloseEvent *event) override;

    ~diaryread(); // 析构函数

signals:
    void closewidget(); // 关闭窗口信号

public slots:
    // 从本地读取日记
    void local_diary_read();

private slots:
    void on_searchbutton_clicked(); // 槽函数：处理搜索按钮点击事件
    void on_compress_donwload_clicked(); // 槽函数：处理压缩下载按钮点击事件

private:
    Ui::diaryread *ui; // 界面元素指针
    QButtonGroup *button_group; // 按钮组，用于评分按钮
    diary info; // 存储当前日记信息
};

#endif // DIARYREAD_H
