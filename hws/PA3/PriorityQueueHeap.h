#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>

using namespace std;

template <typename Type>
class PriorityQueueHeap : public AbstractPriorityQueue<Type> {
private:
    Type *arr;
    int capacity;
    int size;
    
    void minHeapify(int i);
    void bubbleUp(int i);
    int pq_parent(int i);

public:
    PriorityQueueHeap();

    ~PriorityQueueHeap();

    int pq_size();
    
    Type pq_get_min();

    void pq_insert(Type value);

    Type pq_delete();
};

// Your implementation here

template <typename Type>
PriorityQueueHeap<Type>::PriorityQueueHeap() : capacity(10), arr(nullptr), size(0){
    arr = new Type[capacity];
}

template <typename Type>
PriorityQueueHeap<Type>::~PriorityQueueHeap(){
   delete[] arr;
}

template <typename Type>
int PriorityQueueHeap<Type>::pq_size() {
    return size;
}

template <typename Type>
int PriorityQueueHeap<Type>::pq_parent(int i){
    return (i-1)/2;
}

template <typename Type>
Type PriorityQueueHeap<Type>::pq_get_min(){
    if(size == 0){
        throw std::out_of_range("empty priority queue heap bro");
    }
    return arr[0];
}

template <typename Type>
void PriorityQueueHeap<Type>::pq_insert(Type x) {
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


template <typename Type>
void PriorityQueueHeap<Type>::bubbleUp(int i){
    while(arr[pq_parent(i)] > arr[i] && i > 0){
        std::swap(arr[pq_parent(i)], arr[i]);
        i = pq_parent(i);
    }
}

template <typename Type>
Type PriorityQueueHeap<Type>::pq_delete(){
    if(size == 0){
        throw std::out_of_range("empty priority queue heap bro");
    }
    Type temp = arr[0];
    arr[0] = arr[size-1];
    --size;
    minHeapify(0);
    return temp;
}

template <typename Type>
void PriorityQueueHeap<Type>::minHeapify(int i){
    int temp = i;

    if (i * 2 + 1 < size && arr[temp] > arr[i * 2 + 1]){
        temp = i * 2 + 1;
    }

    if (i * 2 + 2 < size && arr[temp] > arr[i * 2 + 2]){
        temp = i * 2 + 2;
    }

    if (i != temp) {
        std::swap(arr[i], arr[temp]);
        minHeapify(temp);
    }
}

#endif