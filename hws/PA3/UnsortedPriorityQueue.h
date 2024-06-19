#ifndef UNSORTED_PRIORITY_QUEUE_H
#define UNSORTED_PRIORITY_QUEUE_H

#include "AbstractPriorityQueue.h"

template <typename Type>
class UnsortedPriorityQueue : public AbstractPriorityQueue<Type> {
    private:
        Type *arr;
        int capacity;
        int size;

    public:
        UnsortedPriorityQueue();

        ~UnsortedPriorityQueue();

        void pq_insert(Type value);

        Type pq_delete();

        Type pq_get_min();

        int pq_size();

        Type get(int ind);
};

template <typename Type>
UnsortedPriorityQueue<Type>::UnsortedPriorityQueue() : capacity(10), size(0), arr(nullptr) {
    arr = new Type[capacity];
}

template <typename Type>
UnsortedPriorityQueue<Type>::~UnsortedPriorityQueue(){
    delete[] arr;
}

template <typename Type>
void UnsortedPriorityQueue<Type>::pq_insert(Type value) {
    if(size == capacity){
        capacity *= 2;
        Type* temp = new Type[capacity];
        for(int i = 0; i < size; ++i){
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }
    arr[size] = value;
    ++size;
}

template <typename Type>
Type UnsortedPriorityQueue<Type>::pq_delete(){
    if (size == 0)
    {
        throw std::out_of_range("empty priority queue");
    }
    int ind = 0;
    for (int i = 1; i < size; ++i) 
    {
        if (arr[i] < arr[ind]) 
        {
            ind = i;
        }
    }
    Type toDelete = arr[ind];
    arr[ind] = arr[size - 1]; 
    --size;
    return toDelete;
}

template <typename Type>
Type UnsortedPriorityQueue<Type>::pq_get_min(){
    if(size == 0){
        throw std::out_of_range("empty priority queue");
    }
    Type min = arr[0];
    for(int i = 1; i < size; ++i){
        if(arr[i] < min){
            min = arr[i];
        }
    }
    return min;

}

template <typename Type>
int UnsortedPriorityQueue<Type>::pq_size(){
    return size;
}

template <typename Type>
Type UnsortedPriorityQueue<Type>::get(int ind){
    return arr[ind];
}

#endif