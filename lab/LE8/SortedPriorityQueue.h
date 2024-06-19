#ifndef SORTED_PRIORITY_QUEUE_H
#define SORTED_PRIORITY_QUEUE_H

template <typename Type>
class SortedPriorityQueue {
    private:
        Type *arr;
        int capacity;
        int startIndex;
        int size;

    public:
        SortedPriorityQueue();

        ~SortedPriorityQueue();

        void pq_insert(Type value);

        Type pq_delete();

        Type pq_get_min();

        int pq_size();
};

template <typename Type>
SortedPriorityQueue<Type>::SortedPriorityQueue() : capacity(10), size(0), arr(nullptr){
   arr = new Type[capacity];
}

template <typename Type>
SortedPriorityQueue<Type>::~SortedPriorityQueue(){
   delete[] arr;
}

template <typename Type>
void SortedPriorityQueue<Type>::pq_insert(Type value) {
    if (size == capacity)
    {
        capacity *= 2;
        Type* temp = new Type[capacity];
        for (int i = 0; i < size; ++i)
        {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }

    int count = size - 1;
    while (count >= 0 && arr[count] > value)
    {
        arr[count + 1] = arr[count];
        --count;
    }
    arr[count + 1] = value;
    ++size;
}

template <typename Type>
Type SortedPriorityQueue<Type>::pq_delete(){
        if (size == 0)
    {
        throw std::out_of_range("empty pq bro");
    }

    Type toDelete = arr[0];
    for (int i = 1; i < size; ++i)
    {
        arr[i-1] = arr[i];
    }
    --size;
    return toDelete;
}

#endif