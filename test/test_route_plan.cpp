#include "route_plan.h"
#include <QString>
#include <iostream>

using namespace std;
int main(){
    // Test the route_plan class
    route_plan rp;
    
    // Load the data from a JSON file
    QString filename = "D:\\code\\project_ds_design\\travel-system-BUPT\\data\\map_of_bupt.geojson";
    rp.load(filename);
    std::cout << "Data loaded successfully!" << std::endl;
    // Create the graph
    rp.create_graph();
    std::cout << "Graph created successfully!" << std::endl;
    // Perform Dijkstra's algorithm
    rp.put_path();
    std::cout << "Dijkstra's algorithm executed successfully!" << std::endl;
    return 0;
}