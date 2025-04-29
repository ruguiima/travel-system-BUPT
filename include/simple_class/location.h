#ifndef LOCATION_H
#define LOCATION_H
#include <string>
#include <QString>
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
    float food;
    float trip;
    float sport;
    float study;
};

#endif // LOCATION_H
