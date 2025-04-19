#ifndef TOPKALGORITHM_HPP
#define TOPKALGORITHM_HPP

#include <queue>
#include <vector>
#include <algorithm>
#include <string>

// 数据库或类对象中的数据结构定义（与你的文档一致）
struct Location {
    int id;
    std::string title;
    int type;         // 0-景点，1-学校
    int popularity;
    float score;
    int score_number;  // 评分人数（备用）
};

struct Diary {
    int id;
    std::string title;
    int site_id;       // 关联的景点id
    int author;
    int popularity;
    float score;
    int score_number;  // 评分人数（备用）
};

// 综合评分计算函数
template<typename T>
inline float calculate_score(const T& item) {
    // 加权公式：热度权重0.6 + 评分权重0.4（可根据需求调整）
    return item.popularity * 0.6f + item.score * 0.4f;
}

// 最小堆比较器（按综合评分升序排列）
template<typename T>
struct CompareScore {
    bool operator()(const T& a, const T& b) {
        return calculate_score(a) > calculate_score(b);
    }
};

// Top-K算法模板类
template<typename T>
class TopKAlgorithm {
public:
    static std::vector<T> get_top_k(const std::vector<T>& items, int k) {
        std::priority_queue<T, std::vector<T>, CompareScore<T>> min_heap;
        
        // 初始化堆：插入前k个元素
        for (int i = 0; i < std::min(k, (int)items.size()); ++i) {
            min_heap.push(items[i]);
        }
        
        // 处理剩余元素
        for (size_t i = k; i < items.size(); ++i) {
            if (calculate_score(items[i]) > calculate_score(min_heap.top())) {
                min_heap.pop();
                min_heap.push(items[i]);
            }
        }
        
        // 提取结果并逆序（从高到低）
        std::vector<T> result;
        while (!min_heap.empty()) {
            result.push_back(min_heap.top());
            min_heap.pop();
        }
        std::reverse(result.begin(), result.end());
        return result;
    }
};
#endif // TOPKALGORITHM_HPP