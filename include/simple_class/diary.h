#ifndef DIARY_H
#define DIARY_H
#include<string>

class diary
{
public:
    int id;
    std::string title;
    std::string context;
    int site_id;
    int author;
    std::string author_name;
    int popularity;
    float score;
    int score_number;
    std::string image_path;
};

#endif // DIARY_H
