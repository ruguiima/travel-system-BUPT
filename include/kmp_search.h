#ifndef KMP_SEARCH_H
#define KMP_SEARCH_H

#include "tool_class/read_data.h"  

class KMP {
private:
    // 构建部分匹配表（next数组）
    static std::vector<int> buildNext(const std::string& pattern);
    

public:
    // KMP核心匹配算法
    static bool kmpMatch(const std::string& text, const std::string& pattern);

};

#endif // KMP_SEARCH_H
