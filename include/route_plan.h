#include <QString>
#include <vector>
#include <cmath>
#include <simple_class/map_elements.h>



class route_plan {
public:
    std::vector<place> places;
    std::vector<road> roads;
    std::vector< std::vector<place_info> > graph_d;
    std::vector< std::vector<place_info> > graph_t;
    std::vector< std::vector<place_info> > graph_m;

    void load(QString file_path);
    void create_graph();
    void put_path();
    static double shortest_path(int start, const std::vector<int>& end, std::vector< std::vector<place_info> >& graph, std::vector<place_info>& record);




};
