#ifndef STACK_LinkedList_H
#define STACK_LinkedList_H
#include "AbstractStack.h"

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
};

template <typename T>
class StackLinkedList : public AbstractStack<T>{
private:
    Node<T>* head;
    int length;
public:
    StackLinkedList();

    ~StackLinkedList();

    StackLinkedList(const StackLinkedList& other);

    StackLinkedList& operator=(const StackLinkedList& other);

    bool isEmpty();

    int size();

    T& top();

    T pop();

    void push(const T& e);

};

// Your implementation here
template <typename T>
StackLinkedList<T>::StackLinkedList() : head(nullptr), length(0){
}

template <typename T>
StackLinkedList<T>::~StackLinkedList(){
    while(head != nullptr){
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    length = 0;
}

template <typename T>
StackLinkedList<T>::StackLinkedList(const StackLinkedList& other) : head(nullptr), length(0) {
    head = new Node<T>;
    Node<T>* otherCurr = other.head;
    head->data = otherCurr->data;
    //head->next = otherCurr->next;
    Node<T>* curr = head;
    otherCurr = otherCurr->next;
    while(otherCurr != nullptr){
       curr->next = new Node<T>;
       curr->next->data = otherCurr->data;
       curr->next->next = otherCurr->next;
       curr = curr->next;
       otherCurr = otherCurr->next;
    }
    length = other.length;
}

template <typename T>
StackLinkedList<T>& StackLinkedList<T>::operator=(const StackLinkedList& other) {

    if(this != &other){
        
        while(!isEmpty()){
            pop();
        }


        head = new Node<T>;
        Node<T>* otherCurr = other.head;
        head->data = otherCurr->data;
        head->next = otherCurr->next;
        Node<T>* curr = head;
        otherCurr = otherCurr->next;

        while(otherCurr != nullptr){
            curr->next = new Node<T>;
            curr->next->data = otherCurr->data;
            curr->next->next = otherCurr->next;
            curr = curr->next;
            otherCurr = otherCurr->next;
        }
    }
    length = other.length;
    return *this;
}

template <typename T>
bool StackLinkedList<T>::isEmpty(){
    return head == nullptr;
}

template <typename T>
int StackLinkedList<T>::size(){
    return length;
}

template <typename T>
T& StackLinkedList<T>::top(){
    if(isEmpty()){
        throw std::out_of_range("Empty stack");
    }
    return head->data;
}

template <typename T>
T StackLinkedList<T>::pop(){
    if(!isEmpty()){
        T popped = head->data;
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        --length;
        return popped;
    }
    else{
        throw std::out_of_range("Empty stack");
    }
}

template <typename T>
void StackLinkedList<T>::push(const T& e){
    ++length;
    Node<T>* node = new Node<T>;
    node->data = e;
    node->next = head;
    head = node;
}


#endif