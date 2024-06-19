#ifndef DEQUE_H
#define DEQUE_H

#include "node.h"
using namespace std;

template <class Type>
class Deque {
private:
	int s;
	Node<Type>* firstNode;
	Node<Type>* lastNode;

public:
	Deque();
	Deque(const Deque& other); 
	Deque& operator=(const Deque& other); 
	~Deque();
	bool isEmpty();
	int size();
	Type first();
	Type last();
	void insertFirst(Type o);
	void insertLast(Type o);
	Type removeFirst();
	Type removeLast();
	Type get(int ind);
};

// Your implementation here 

template <class Type>
Deque<Type>::Deque() : firstNode(nullptr), lastNode(nullptr), s(0){}

template <class Type>
Deque<Type>::~Deque() {
	while(firstNode != nullptr){
		Node<Type>* temp = firstNode;
		firstNode = firstNode->getNext();
		delete temp;
	}
	s = 0;
}

template <class Type>
Deque<Type>::Deque(const Deque& other) : firstNode(nullptr), lastNode(nullptr), s(0) {
	Node<Type>* otherCurr = other.firstNode;
	while(otherCurr != nullptr){
		insertLast(otherCurr->getData());
		otherCurr = otherCurr->getNext();
	}
}

template <class Type>
Deque<Type>& Deque<Type>::operator=(const Deque& other) {
	if(this != &other){
		while(!isEmpty()){
			removeFirst();
		}
		Node<Type>* otherCurr = other.firstNode;
		while(otherCurr != nullptr){
			insertLast(otherCurr->getData());
			otherCurr = otherCurr->getNext();
		}
	}
	return *this;
}

template <class Type>
bool Deque<Type>::isEmpty() {
	return s == 0;
}

template <class Type>
int Deque<Type>::size() {
	return s;
}

template <class Type>
Type Deque<Type>::first() {
	if(isEmpty()){
		return Type();
	}
	return firstNode->getData();
}

template <class Type>
Type Deque<Type>::last() {
	if(isEmpty()){
		return Type();
	}
	return lastNode->getData();
}

template <class Type>
void Deque<Type>::insertFirst(Type o) {
	Node<Type>* node = new Node<Type>(o);
	if(firstNode == nullptr){
		lastNode = node;
		firstNode = node;
	}
	else{
		firstNode->setPrev(node);
		node->setNext(firstNode);
		firstNode = node;
	}
	++s;
}

template <class Type>
void Deque<Type>::insertLast(Type o) {
	Node<Type>* node = new Node<Type>(o);
	if(lastNode == nullptr || firstNode == nullptr){
		lastNode = node;
		firstNode = node;
	}
	else{
		lastNode->setNext(node);
		node->setPrev(lastNode);
		lastNode = node;
	}
	++s;
}

template <class Type>
Type Deque<Type>::removeFirst() {
	if(isEmpty()){
		throw std::out_of_range("empty deque bro");
	}
	Node<Type>* temp = firstNode;
	Type data = temp->getData();
	firstNode = firstNode->getNext();
	delete temp;
	--s;
	return data;
}

template <class Type>
Type Deque<Type>::removeLast() {
	if(isEmpty()){
		throw std::out_of_range("empty deque bro");
	}
	Node<Type>* temp = lastNode;
	Type data = temp->getData();
	lastNode = lastNode->getPrev();
	delete temp;
	if (size() == 1) { // handle this case to avoid double free in destructor
        firstNode = nullptr;
    }
    else {
        lastNode->setNext(nullptr);
    }
	--s;
	return data;
}
template <class Type>
Type Deque<Type>::get(int ind){
	Node<Type>* curr = firstNode;
	int count = 0;
	while(curr != nullptr){
		if(count == ind){
			return curr->getData();
		}
		curr = curr->getNext();
		++count;
	}
	throw std::out_of_range("didnt work bro");
}

#endif
