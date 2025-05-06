#ifndef TOPKALGORITHM_H
#define TOPKALGORITHM_H

#include <vector>
#include <algorithm>


template<typename T, typename criteria>
class my_pq {
private:
    std::vector<T> heap;
    criteria cmp;
public:
    my_pq(criteria cmp) : cmp(cmp) {}
    // 修改push和pop函数为自实现
    void push(const T& item){
        // 目前使用标准库维护堆，请修改为自实现
        heap.push_back(item);
        std::push_heap(heap.begin(), heap.end(), cmp);
    }
    void pop(){
        // 目前使用标准库维护堆，请修改为自实现
        std::pop_heap(heap.begin(), heap.end(), cmp);
        heap.pop_back();
    }
    const T& top() const{
        return heap.front();
    }
    bool empty() const{
        return heap.empty();
    }
};
// Top-K算法实现
template<typename T, typename criteria>
std::vector<T> getTopK(const std::vector<T>& items, int k, criteria cmp) {
    my_pq<T, criteria> minHeap(cmp);

    // 初始化堆
    for (int i = 0; i < std::min(k, (int)items.size()); ++i) {
        minHeap.push(items[i]);
    }

    // 处理剩余元素
    for (size_t i = k; i < items.size(); ++i) {
        if (cmp(items[i], minHeap.top())) {
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



#endif // TOPKALGORITHM_H
