#include "top_k_algorithm.h"
#include "tool_class/read_data.h"
#include "simple_class/diary.h"
#include "simple_class/location.h"  // 确保包含数据库数据结构定义

// 综合评分计算函数实现
template<typename T>
float calculateScore(const T& item, sortCriteria criteria) {
    if (criteria == byHeat) {
        return item.popularity;
    } else {
        return item.score;
    }
}

// 比较器实现
template<typename T, sortCriteria criteria>
bool compareScore<T, criteria>::operator()(const T& a, const T& b) {
    return calculateScore(a, criteria) > calculateScore(b, criteria);
}

// Top-K算法实现
template<typename T, sortCriteria criteria>
std::vector<T> topKAlgorithm<T, criteria>::getTopK(const std::vector<T>& items, int k) {
    std::priority_queue<T, std::vector<T>, compareScore<T, criteria>> minHeap;

    // 初始化堆
    for (int i = 0; i < std::min(k, (int)items.size()); ++i) {
        minHeap.push(items[i]);
    }

    // 处理剩余元素
    for (size_t i = k; i < items.size(); ++i) {
        if (calculateScore(items[i], criteria) > calculateScore(minHeap.top(), criteria)) {
            minHeap.pop();
            minHeap.push(items[i]);
        }
    }

    // 提取结果
    std::vector<T> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }
    std::reverse(result.begin(), result.end());
    return result;
}

// 显式实例化模板（使用数据库中的实际数据结构）
template class topKAlgorithm<location, byHeat>;
template class topKAlgorithm<location, byScore>;
template class topKAlgorithm<diary, byHeat>;
template class topKAlgorithm<diary, byScore>;
