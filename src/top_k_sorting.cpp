#include "top_k_algorithm.h"
 
/**
 * @brief 计算项目的综合评分 
 * @tparam T 项目类型（Location或Diary）
 * @param item 待计算的项目 
 * @param criteria 排序标准（BY_HEAT按热度，其他按分数）
 * @return 项目的综合评分 
 */
template<typename T>
float calculate_score(const T& item, SortCriteria criteria) {
    if (criteria == BY_HEAT) {
        return item.popularity;   // 如果按热度排序，返回popularity字段 
    } else {
        return item.score;       // 否则返回score字段 
    }
}
 
/**
 * @brief 比较器类的运算符重载 
 * @tparam T 项目类型 
 * @tparam Criteria 排序标准 
 * @param a 第一个比较项目 
 * @param b 第二个比较项目 
 * @return 返回a的评分是否大于b的评分 
 */
template<typename T, SortCriteria Criteria>
bool CompareScore<T, Criteria>::operator()(const T& a, const T& b) {
    return calculate_score(a, Criteria) > calculate_score(b, Criteria);
}
 
/**
 * @brief 获取Top-K项目的实现 
 * @tparam T 项目类型 
 * @tparam Criteria 排序标准 
 * @param items 所有待排序的项目集合 
 * @param k 需要返回的Top-K数量 
 * @return 排序后的Top-K项目集合 
 */
template<typename T, SortCriteria Criteria>
std::vector<T> TopKAlgorithm<T, Criteria>::get_top_k(const std::vector<T>& items, int k) {
    // 使用最小堆来维护Top-K元素 
    std::priority_queue<T, std::vector<T>, CompareScore<T, Criteria>> min_heap;
 
    // 初始化堆：先放入前k个元素（或全部元素如果总数不足k）
    for (int i = 0; i < std::min(k, (int)items.size());  ++i) {
        min_heap.push(items[i]); 
    }
 
    // 处理剩余元素：如果当前元素比堆顶（当前最小值）大，则替换 
    for (size_t i = k; i < items.size();  ++i) {
        if (calculate_score(items[i], Criteria) > calculate_score(min_heap.top(),  Criteria)) {
            min_heap.pop(); 
            min_heap.push(items[i]); 
        }
    }
 
    // 提取结果：堆中元素现在是Top-K，但顺序是升序的 
    std::vector<T> result;
    while (!min_heap.empty())  {
        result.push_back(min_heap.top()); 
        min_heap.pop(); 
    }
    // 反转结果使其变为降序排列（从高到低）
    std::reverse(result.begin(),  result.end()); 
    return result;
}
 
// 显式实例化模板（解决链接问题）
// 为Location和Diary两种类型，BY_HEAT和BY_SCORE两种排序标准生成具体实现 
template class TopKAlgorithm<Location, BY_HEAT>;
template class TopKAlgorithm<Location, BY_SCORE>;
template class TopKAlgorithm<Diary, BY_HEAT>;
template class TopKAlgorithm<Diary, BY_SCORE>;