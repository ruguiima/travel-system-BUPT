#include "route_plan.h"
#include <QString>
#include <iostream>
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
    return 0;
}
