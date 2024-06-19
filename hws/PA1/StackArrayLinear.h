#ifndef STACK_LINEAR_ARRAY_H
#define STACK_LINEAR_ARRAY_H
#include "AbstractStack.h"

template <typename T>
class StackArrayLinear : public AbstractStack<T> {
private:
    T* data;
    int length;
    int topIndex;

public:
    StackArrayLinear();

    ~StackArrayLinear();

    StackArrayLinear(const StackArrayLinear& other);

    StackArrayLinear& operator=(const StackArrayLinear& other);

    bool isEmpty();

    int size();

    T& top();

    T pop();

    void push(const T& e);

};

// Your implementation here
template <typename T>
StackArrayLinear<T>::StackArrayLinear() : data(new T[1]), length(1), topIndex(-1) {}

template <typename T>
StackArrayLinear<T>::~StackArrayLinear(){
    delete[] data;
}

template <typename T>
StackArrayLinear<T>::StackArrayLinear(const StackArrayLinear& other) : data(new T[other.length]), length(other.length), topIndex(other.topIndex) {
    for(int i = 0; i < other.length; ++i){
        data[i] = other.data[i];
    }
}

template <typename T>
StackArrayLinear<T>& StackArrayLinear<T>::operator=(const StackArrayLinear& other) {
    if(this != &other){
        delete[] data;
        length = other.length;
        topIndex = other.topIndex;
        data = new T[length];
        for(int i = 0; i <= topIndex; ++i){
            data[i] = other.data[i];
        }
    }
    return *this;
}

template <typename T>
bool StackArrayLinear<T>::isEmpty(){
    if(topIndex == -1){
        return true;
    }
    return false;
}

template <typename T>
int StackArrayLinear<T>::size(){
    return topIndex + 1;
}

template <typename T>
T& StackArrayLinear<T>::top(){
    if(isEmpty()){
        throw std::out_of_range("Empty stack");
    }
    return data[topIndex];
}

template <typename T>
T StackArrayLinear<T>::pop(){
    if(!isEmpty()){
        T popped = data[topIndex];
        --topIndex;
        return popped;
    }
    else{
        throw std::out_of_range("Empty stack");
    }
}

template <typename T>
void StackArrayLinear<T>::push(const T& e){
    if(topIndex + 1 == length){ // if the array is at maximum capacity, resize array. if not, then just increase top ind and push value to top
        T* temp = new T[length + 10];
        for(int i = 0; i < length; ++i){
            temp[i] = data[i];
        }
        length += 10;
        delete[] data;
        data = temp;
    }
    ++topIndex;
    data[topIndex] = e;
}

#endif