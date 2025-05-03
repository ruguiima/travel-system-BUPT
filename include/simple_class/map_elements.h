#ifndef MAP_ELEMENTS_H
#define MAP_ELEMENTS_H

#include <QString>

using coor = std::pair<double, double>;

class place {
public:
    place(coor loct, const QString &name, const QString &type)
        : loct(loct), name(name), type(type) {}
    coor getLoct() const { return loct; }
    QString getName() const { return name; }
    QString getType() const { return type; }
private:
    coor loct;
    QString name;
    QString type;
};

enum road_type {cycleway, sidewalk};

class road {
public:
    road(coor start, coor end,  road_type type, double cong)
        : start(start), end(end),  type(type), cong(cong) {}
    coor getStart() const { return start; }
    coor getEnd() const { return end; }
    double getLength() const { return length; }
    road_type getType() const { return type; }
    double getCong() const { return cong; }

    void calcu_leng();
private:
    coor start, end;
    double length;
    road_type type;
    double cong;
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
    int id;
    double weight;
    road_type type;
};
#endif // MAP_ELEMENTS_H
