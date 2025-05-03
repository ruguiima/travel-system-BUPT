#include "kmp_search.h"
#include <algorithm>
#include <cstring>

// ---------- KMP算法核心实现 ----------
// 实现部分匹配表构建
std::vector<int> KMP::buildNext(const std::string& pattern) {
    int n = pattern.length();
    std::vector<int> next(n, 0);
    
    for (int i = 1, j = 0; i < n; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        next[i] = j;
    }
    return next;
}

// KMP匹配算法实现
bool KMP::kmpMatch(const std::string& text, const std::string& pattern) {
    std::vector<int> next = buildNext(pattern);
    int n = text.length();
    int m = pattern.length();
    
    for (int i = 0, j =  0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            return true;
        }
    }
    return false;
}

// 转换为小写（支持大小写不敏感）
std::string KMP::toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
        [](unsigned char c){ return std::tolower(c); });
    return lowerStr;
}


// ---------- 日记搜索逻辑 ----------
bool KMP::matchDiary(const diary& diary,
                    const std::string& keyword,
                    bool searchTitle,
                    bool searchContent,
                    bool searchAuthor,
                    bool searchSite) 
{
    std::string lowerKeyword = toLower(keyword);
    
    // 检查标题
    if (searchTitle && kmpMatch(toLower(diary.title), lowerKeyword)) return true;
    
    // 检查内容
    if (searchContent && kmpMatch(toLower(diary.context), lowerKeyword)) return true;
    
    // 检查作者
    if (searchAuthor && kmpMatch(toLower(diary.author_name), lowerKeyword)) return true;
    
    // 检查关联景点ID（转为字符串匹配）
    if (searchSite && kmpMatch(std::to_string(diary.site_id), lowerKeyword)) return true;
    
    return false;
}

std::vector<diary> KMP::searchDiaries(
    const std::vector<diary>& diaries,
    const std::string& keyword,
    bool searchTitle,
    bool searchContent,
    bool searchAuthor,
    bool searchSite) 
{
    std::vector<diary> results;
    for (const auto& diary : diaries) {
        if (matchDiary(diary, keyword, searchTitle, searchContent, searchAuthor, searchSite)) {
            results.push_back(diary);
        }
    }
    return results;
}

// ---------- 景点搜索逻辑 ----------
bool KMP::matchLocation(const location& location,
                       const std::string& keyword,
                       bool searchName)
{
    std::string lowerKeyword = toLower(keyword);
    
    // 检查名称
    if (searchName && kmpMatch(toLower(location.title), lowerKeyword)) return true;
    

    return false;
}

std::vector<location> KMP::searchLocations(
    const std::vector<location>& locations,
    const std::string& keyword,
    bool searchName)
{
    std::vector<location> results;
    for (const auto& location : locations) {
        if (matchLocation(location, keyword, searchName)) {
            results.push_back(location);
        }
    }
    return results;
}
