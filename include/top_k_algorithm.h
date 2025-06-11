#ifndef TOPKALGORITHM_H
#define TOPKALGORITHM_H

#include <vector>
#include <algorithm>

template<typename T, typename criteria>
class my_pq {
private:
    std::vector<T> heap;
    criteria cmp;

    // 自定义上浮操作（用于push）
    void sift_up(size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (cmp(heap[parent], heap[index])) {
                std::swap(heap[parent], heap[index]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // 自定义下沉操作（用于pop）
    void sift_down(size_t index) {
        size_t size = heap.size();
        while (true) {
            size_t left = 2 * index + 1;
            size_t right = 2 * index + 2;
            size_t largest = index;

            if (left < size && cmp(heap[largest], heap[left])) {
                largest = left;
            }
            if (right < size && cmp(heap[largest], heap[right])) {
                largest = right;
            }

            if (largest != index) {
                std::swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    my_pq(criteria cmp) : cmp(cmp) {}

    // 插入元素到堆中
    void push(const T& item) {
        heap.push_back(item);
        sift_up(heap.size() - 1);  // 上浮操作
    }
    // 弹出堆顶元素
    void pop() {
        if (heap.empty()) return;
        std::swap(heap.front(), heap.back());
        heap.pop_back();
        if (!heap.empty()) {
            sift_down(0);  // 下沉操作
        }
    }
    // 获取堆顶元素
    const T& top() const {
        return heap.front();
    }
    // 堆判空
    bool empty() const {
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
