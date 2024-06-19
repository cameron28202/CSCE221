#ifndef STACK_DOUBLE_ARRAY_H
#define STACK_DOUBLE_ARRAY_H
#include "AbstractStack.h"

template <typename T>
class StackArrayDouble : public AbstractStack<T> {
private:
    T* data; //dynamically allocated 1d array
    int length; //pretty much capacity
    int topIndex; //length-1

public:
    StackArrayDouble();

    ~StackArrayDouble();

    StackArrayDouble(const StackArrayDouble& other);

    StackArrayDouble& operator=(const StackArrayDouble& other);

    bool isEmpty();

    int size();

    T& top();

    T pop();

    void push(const T& e);

};

// Your implementation here
template <typename T>
StackArrayDouble<T>::StackArrayDouble() : data(new T[1]), length(1), topIndex(-1) {}

template <typename T>
StackArrayDouble<T>::~StackArrayDouble(){
    delete[] data;
}

template <typename T>
StackArrayDouble<T>::StackArrayDouble(const StackArrayDouble& other) : data(new T[other.length]), length(other.length), topIndex(other.topIndex) {
    for(int i = 0; i < other.length; ++i){
        data[i] = other.data[i];
    }
}

template <typename T>
StackArrayDouble<T>& StackArrayDouble<T>::operator=(const StackArrayDouble& other) {
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
bool StackArrayDouble<T>::isEmpty(){
    if(topIndex == -1){
        return true;
    }
    return false;
}

template <typename T>
int StackArrayDouble<T>::size(){
    return topIndex + 1;
}

template <typename T>
T& StackArrayDouble<T>::top(){
    if(isEmpty()){
        throw std::out_of_range("Empty stack");
    }
    return data[topIndex];
}

template <typename T>
T StackArrayDouble<T>::pop(){
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
void StackArrayDouble<T>::push(const T& e){
    if(topIndex + 1 == length){ // if the array is at maximum capacity, resize array. if not, then just increase top ind and push value to top
        T* temp = new T[length * 2];
        for(int i = 0; i < length; ++i){
            temp[i] = data[i];
        }
        length *= 2;
        delete[] data;
        data = temp;
    }
    ++topIndex;
    data[topIndex] = e;
}

#endif