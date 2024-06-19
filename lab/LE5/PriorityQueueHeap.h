#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>
#include <iostream>

using namespace std;

template <typename Type, typename Compare = std::greater<Type>>
class PriorityQueueHeap {
private:
    Compare compare;
    Type *arr;
    int capacity;
    int size;

    void heapify(int i);
    void bubbleUp(int i);
    int pq_parent(int i);

public:
    PriorityQueueHeap();

    PriorityQueueHeap(const PriorityQueueHeap& other);

    PriorityQueueHeap(const Compare& comp);

    PriorityQueueHeap& operator=(const PriorityQueueHeap& other);

    ~PriorityQueueHeap();

    int pq_size();

    bool is_pq_empty();
    
    Type pq_top();

    void pq_insert(Type x);

    Type pq_delete();

    Type get(int i);
};

// Your implementation here

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::PriorityQueueHeap() : compare(), capacity(10), arr(nullptr), size(0) {
    arr = new Type[capacity];
}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::~PriorityQueueHeap(){
    delete[] arr;
}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::PriorityQueueHeap(const Compare& _comp) : compare(_comp), capacity(10), arr(nullptr), size(0) {
    arr = new Type[capacity];
}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>::PriorityQueueHeap(const PriorityQueueHeap& other) : compare(other.compare), size(other.size), capacity(other.capacity) {
    arr = new Type[other.capacity];
    for(int i = 0; i < other.size; ++i){
        arr[i] = other.arr[i];
    }
}

template <typename Type, typename Compare>
PriorityQueueHeap<Type, Compare>& PriorityQueueHeap<Type, Compare>::operator=(const PriorityQueueHeap& other) {
    if(this != &other){
        delete[] arr;
        arr = new Type[other.capacity];
        for(int i = 0; i < other.size; ++i){
            arr[i] = other.arr[i];
        }
        compare = other.compare;
        size = other.size;
        capacity = other.capacity;
    }
    return *this;
}

template <typename Type, typename Compare>
int PriorityQueueHeap<Type, Compare>::pq_size() {
    return size;
}

template <typename Type, typename Compare>
bool PriorityQueueHeap<Type, Compare>::is_pq_empty(){
    return size == 0;
}

template <typename Type, typename Compare>
int PriorityQueueHeap<Type, Compare>::pq_parent(int i){
    return (i-1) / 2;
}

template <typename Type, typename Compare>
Type PriorityQueueHeap<Type, Compare>::pq_top(){
    if(is_pq_empty()){
        throw std::out_of_range("empty priority queue heap bro");
    }
    return arr[0];
}

template <typename Type, typename Compare>
void PriorityQueueHeap<Type, Compare>::pq_insert(Type x) {
    if(size == capacity){
        capacity *= 2;
        Type* temp = new Type[capacity];
        for(int i = 0; i < size; ++i){
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }
    arr[size] = x;
    bubbleUp(size);
    ++size;
}


template <typename Type, typename Compare>
void PriorityQueueHeap<Type, Compare>::bubbleUp(int i){
    while(compare(arr[pq_parent(i)], arr[i]) && i > 0){
        std::swap(arr[pq_parent(i)], arr[i]);
        i = pq_parent(i);
    }
}

template <typename Type, typename Compare>
Type PriorityQueueHeap<Type, Compare>::pq_delete(){
    if(is_pq_empty()){
        throw std::out_of_range("empty priority queue heap bro");
    }
    Type temp = arr[0];
    arr[0] = arr[size-1];
    --size;
    heapify(0);
    return temp;
}

template <typename Type, typename Compare>
void PriorityQueueHeap<Type, Compare>::heapify(int i){
    int temp = i;

    if (i * 2 + 1 < size && compare(arr[temp], arr[i * 2 + 1])){
        temp = i * 2 + 1;
    }

    if (i * 2 + 2 < size && compare(arr[temp], arr[i * 2 + 2])){
        temp = i * 2 + 2;
    }

    if (i != temp) {
        std::swap(arr[i], arr[temp]);
        heapify(temp);
    }
    
}
template <typename Type, typename Compare>
Type PriorityQueueHeap<Type, Compare>::get(int i){
    return arr[i];
}

#endif