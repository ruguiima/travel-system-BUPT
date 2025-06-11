#ifndef CAMPUS_NAV_H
#define CAMPUS_NAV_H

#include <QWidget>
#include "route_plan.h"

namespace Ui {
class campus_nav;
}

enum DrawMode {
    None,
    DrawPlaces,
    DrawRoute
};

class campus_nav : public QWidget
{
    Q_OBJECT

public:
    explicit campus_nav(QWidget *parent = nullptr);
    ~campus_nav();
    void show_nearby(std::vector<place> result); // 显示附近场所
    void closeEvent(QCloseEvent *event) override;  // 关闭事件处理


signals:
    void windowclose();  // 窗口关闭信号

private slots:

    void on_pushButton_cur_clicked();  // 更新当前位置
    void on_pushButton_search_clicked();  // 搜索附近场所
    void on_pushButton_dest_clicked(QString place_name);  // 添加目的地
    void onDeleteButtonClicked();  // 删除目的地按钮点击事件
    void on_pushButton_plan_clicked();  // 规划路线
    void on_pushButton_nearby_clicked();  // 显示附近场所
    void on_pushButton_route_clicked();  // 显示规划路线
    void onAddButtonClicked();  // 添加目的地按钮点击事件

private:
    Ui::campus_nav *ui;
    route_plan rp; // 初始化以调用路线规划类功能
    std::unordered_map<QString, int> place_name_to_id;  // 存储场所名称到ID的映射，降低复杂度
    int cur_loc = 0;  // 当前用户位置
    std::vector<place> placesToDraw;  // 存储需要绘制的场所
    std::vector<place_info> routeToDraw;  // 存储需要绘制的路线
    DrawMode currentDrawMode = None;  // 当前绘制模式

    QPointF mapCoordToPixel(coor tar, QRect r);  // 将地图坐标转换为像素坐标

protected:
    void paintEvent(QPaintEvent *event) override;  // 绘制事件处理
};

#endif // CAMPUS_NAV_H
