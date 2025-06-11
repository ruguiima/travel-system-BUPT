#include <QString>
#include <vector>
#include <cmath>
#include <simple_class/map_elements.h>



class route_plan {
public:
    std::vector<place> places;  // 存储所有场所信息
    std::vector<road> roads;   // 存储所有道路信息
    std::vector< std::vector<place_info> > graph_d;  // 存储道路图（距离）
    std::vector< std::vector<place_info> > graph_t;  // 存储道路图（步行时间）
    std::vector< std::vector<place_info> > graph_m;  // 存储道路图（骑行+步行时间）

    void load(QString file_path);  // 加载地图数据
    void create_graph();  // 创建道路图
    void put_path();  
    static double shortest_path(int start, const std::vector<int>& end, 
                                std::vector< std::vector<place_info> >& graph, 
                                std::vector<place_info>& record);  // 求最短路径
    std::vector<place> search_place(int start, double max_dist);  // 搜索场所
};
