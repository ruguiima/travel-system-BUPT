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


