#ifndef TOPKALGORITHM_H
#define TOPKALGORITHM_H

#include <vector>
#include <queue>
#include <algorithm>
#include "database_connection.h"  // 直接使用数据库连接类的数据结构

// 使用数据库中的数据结构（假设已通过 read_data.h 定义）
#include "tool_class/read_data.h"

// 排序依据枚举
enum sortCriteria { byHeat, byScore };

// 综合评分计算函数（声明）
template<typename T>
float calculateScore(const T& item, sortCriteria criteria);

// 最小堆比较器（声明）
template<typename T, sortCriteria criteria>
struct compareScore {
    bool operator()(const T& a, const T& b);
};

// Top-K算法模板类（声明）
template<typename T, sortCriteria criteria>
class topKAlgorithm {
public:
    static std::vector<T> getTopK(const std::vector<T>& items, int k);
};

#endif // TOPKALGORITHM_H