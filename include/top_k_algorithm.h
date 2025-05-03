#ifndef TOPKALGORITHM_H
#define TOPKALGORITHM_H
#include <algorithm>
// 手动实现动态数组
template<typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int size;

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray() : data(new T[1]), capacity(1), size(0) {}
    ~DynamicArray() { delete[] data; }

    void push_back(const T& value) {
        if (size >= capacity) resize(capacity * 2);
        data[size++] = value;
    }

    void pop_back() {
        if (size > 0) --size;
    }

    T& operator[](int index)             { return data[index]; }
    const T& operator[](int index) const { return data[index]; }
    int getSize() const { return size; }
    bool empty() const  { return size == 0; }
};

// 最大堆类（手动实现）
template<typename T, typename Compare>
class MaxHeap {
private:
    DynamicArray<T> heap;
    Compare comp;

    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (comp(heap[parent], heap[index])) {
                std::swap(heap[parent], heap[index]);
                index = parent;
            } else break;
        }
    }

    void siftDown(int index) {
        int maxIndex = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap.getSize() && comp(heap[maxIndex], heap[left]))
            maxIndex = left;
        if (right < heap.getSize() && comp(heap[maxIndex], heap[right]))
            maxIndex = right;
        if (index != maxIndex) {
            std::swap(heap[index], heap[maxIndex]);
            siftDown(maxIndex);
        }
    }

public:
    explicit MaxHeap(const Compare& cmp) : comp(cmp) {}

    void push(const T& value) {
        heap.push_back(value);
        siftUp(heap.getSize() - 1);
    }

    T pop() {
        T root = heap[0];
        heap[0] = heap[heap.getSize() - 1];
        heap.pop_back();
        siftDown(0);
        return root;
    }

    const T& top() const { return heap[0]; }
    bool empty() const { return heap.empty(); }
    int size() const { return heap.getSize(); }
};

struct Location {
    int id;
    const char* title;
    int type;
    int popularity;
    float score;
};

enum SortCriteria { BY_HEAT, BY_SCORE };

struct CompareBy {
    SortCriteria criteria;
    explicit CompareBy(SortCriteria c) : criteria(c) {}

    bool operator()(const Location& a, const Location& b) const {
        // 注意：这里保持最大堆比较逻辑
        if (criteria == BY_HEAT) {
            return a.popularity < b.popularity; // 最大堆需要a < b时交换
        } else {
            return a.score < b.score;
        }
    }
};

class TopKAlgorithm {
public:
    static DynamicArray<Location> getTopK(
        Location* items, int n, int k, SortCriteria criteria
        );
};

#endif // TOPKALGORITHM_HPP
