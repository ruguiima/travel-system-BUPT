#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
#include <fstream>
using namespace std;

//头文件
//尽量遵循成员变量私有，函数可公可私
enum road_type {cycleway, path};
struct coordinate {
    int x;
    int y;
};

struct place {
    place(int id, string name, coordinate location, string type) : 
        id(id), name(name), location(location), type(type) {}
    place () = default;
    int id;
    string name;
    coordinate location;
    string type;
};

struct road {
    vector<coordinate> path; 
    int start_id;
    int end_id;
    double length;
    double congestion;
    road_type type;
    double weight;
};

class Map {
public:
    Map();
    ~Map() = default;
    void load_places(string filename);
    void load_roads(string filename);
    void design_path(int start_id, int end_id);
    void sort_by_dist(int refer_id);
private:
    vector<place> places;
    vector<road> roads;
    map<int, vector<pair<int, double>>> graph;

};

class MySort {
public:
    template <typename T,typename Compare>
    static void my_sort(vector<T>& array,Compare comp) {
        sort(array.begin(), array.end(), comp);
    }
};

//实现
Map::Map() {
    load_places("places.txt");
    load_roads("roads.txt");
}

void Map::load_places(string filename) {
    // Load places from file
    ifstream file(filename);
    place p(0, "", {0, 0}, "");
    file >> p.id >> p.name >> p.location.x >> p.location.y >> p.type;
    places.push_back(p);
    file.close();

}

void Map::load_roads(string filename) {
    // Load roads from file
}

void Map::design_path(int start_id, int end_id) {
    // Design path from start_id to end_id
}

void Map::sort_by_dist(int refer_id) {

    MySort::my_sort(places, [refer_id, this](const place& a, const place& b) {
        double dist_a = pow(a.location.x - places[refer_id].location.x,2) + pow(a.location.y - places[refer_id].location.y,2);
        double dist_b = pow(b.location.x - places[refer_id].location.x,2) + pow(b.location.y - places[refer_id].location.y,2);
        return dist_a < dist_b;
    });
}


int main() {
    Map map;
    map.sort_by_dist(0);
    return 0;
}
