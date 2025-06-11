#ifndef MAP_ELEMENTS_H
#define MAP_ELEMENTS_H

#include <QString>

using coor = std::pair<double, double>;
double calcu_length(coor start, coor end);

class place {
public:
    place(coor loct, const QString &name, const QString &type)
        : loct(loct), name(name), type(type) {}
    coor getLoct() const { return loct; }
    QString getName() const { return name; }
    QString getType() const { return type; }
    double dist;  //可变成员变量，在场所查询时存储离当前位置的距离
private:
    coor loct;  //坐标
    QString name;  //场所名称
    QString type;  //场所类别
};

enum road_type {cycleway, sidewalk};

class road {
public:
    road(coor start, coor end,  road_type type, double cong)
        : start(start), end(end),  type(type), cong(cong) {}
    coor getStart() const { return start; }
    coor getEnd() const { return end; }
    void setLength(double len) { length = len; }
    double getLength() const { return length; }
    road_type getType() const { return type; }
    double getCong() const { return cong; }
private:
    coor start, end;  //始终点坐标
    double length;  //道路长度
    road_type type;  //道路类型（人行道/车道）
    double cong;  //拥挤度
};

class place_info {
public:
    place_info(int id, double weight, road_type type)
        : id(id), weight(weight), type(type) {}
    place_info() = default;
    int getId() const { return id; }
    double getWeight() const { return weight; }
    road_type getType() const { return type; }
private:
    int id;  //场所ID
    double weight;  //权重（距离或时间）
    road_type type;  //道路类型（人行道/车道）
};
#endif // MAP_ELEMENTS_H
