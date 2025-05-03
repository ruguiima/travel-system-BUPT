#ifndef KMP_SEARCH_H
#define KMP_SEARCH_H

#include "tool_class/read_data.h"  

class KMP {
private:
    // 构建部分匹配表（next数组）
    static std::vector<int> buildNext(const std::string& pattern);
    
    // KMP核心匹配算法
    static bool kmpMatch(const std::string& text, const std::string& pattern);
    
    // 统一转换为小写（实现大小写不敏感）
    static std::string toLower(const std::string& str);

public:
    // ---------- 日记搜索接口 ----------
    static std::vector<diary> searchDiaries(
        const std::vector<diary>& diaries,
        const std::string& keyword,
        bool searchTitle = true,
        bool searchContent = true,
        bool searchAuthor = true,
        bool searchSite = true
    );
    
    // ---------- 景点搜索接口 ----------
    static std::vector<location> searchLocations(
        const std::vector<location>& locations,
        const std::string& keyword,
        bool searchName = true
    );

private:
    // 单个日记匹配检查
    static bool matchDiary(const diary& diary,
                         const std::string& keyword,
                         bool searchTitle,
                         bool searchContent,
                         bool searchAuthor,
                         bool searchSite);
    
    // 单个景点匹配检查
    static bool matchLocation(const location& location,
                             const std::string& keyword,
                             bool searchName);
};

#endif // KMP_SEARCH_H
