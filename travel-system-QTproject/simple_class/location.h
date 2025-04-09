#ifndef LOCATION_H
#define LOCATION_H
#include <string>
class location
{
public:
    int id;
    std::string title;
    int type;
    int popularity;
    float score;
    int score_number;
    std::string image_path;
};

#endif // LOCATION_H
