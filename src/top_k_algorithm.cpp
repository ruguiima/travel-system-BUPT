#include "top_k_algorithm.h"

// 手动实现Top-K算法
DynamicArray<Location> TopKAlgorithm::getTopK(
    Location* items, int n, int k, SortCriteria criteria
    ) {
    DynamicArray<Location> result;
    if (k <= 0 || n <= 0) return result;
    k = (k > n) ? n : k; // 处理k > n的情况

    CompareBy comp(criteria);
    MaxHeap<Location, CompareBy> maxHeap(comp);

    // 第一阶段：填充前k个元素
    for (int i = 0; i < k; ++i) {
        maxHeap.push(items[i]);
    }

    // 第二阶段：维护最大堆
    for (int i = k; i < n; ++i) {
        if (comp(items[i], maxHeap.top())) {
            maxHeap.pop();
            maxHeap.push(items[i]);
        }
    }

    // 第三阶段：直接输出堆中元素（已按从大到小排序）
    while (!maxHeap.empty()) {
        result.push_back(maxHeap.pop());
    }

    return result;
}
