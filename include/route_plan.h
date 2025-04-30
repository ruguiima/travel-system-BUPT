#include <QString>
#include <vector>
#include <cmath>

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


class route_plan {
public:
    void load(QString file_path);
    void create_graph();
    static double dijkstra(int start, int end, std::vector< std::vector<place_info> >& graph, std::vector<place_info>& record);
    void put_path();
    static double shortest_path(int start, const std::vector<int>& end, std::vector< std::vector<place_info> >& graph, std::vector<place_info>& record);
private:
    std::vector<place> places;
    std::vector<road> roads;
    std::vector< std::vector<place_info> > graph_d;
    std::vector< std::vector<place_info> > graph_t;
    std::vector< std::vector<place_info> > graph_m;


};
