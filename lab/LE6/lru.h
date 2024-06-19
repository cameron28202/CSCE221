//Least Recently Used Cache Implementation
// The size of the Cache is limited to maxSize. If the cache is full and we want to insert a new item, we remove the least recently used item from the cache.
// Implement with O(1) time complexity the following functions:
    // 1. insertKeyValue(string key, int value) - insert a key value pair into the cache. If the key already exists, update the value of the key.
    // 2. getValue(string key) - return the value of the key if it exists, otherwise return NULL.
    // 3. mostRecentKey() - return the key of the most recently used value.

#ifndef LRU_H
#define LRU_H

#include <iostream>
#include <list>
#include <unordered_map>
using namespace std;

class Node {
public:
	string key;
	int value;
	Node (string key,int value) {
		this->key = key;
		this->value = value;
	}
};

class LRUCache{
private: 
	int maxSize;
	list<Node> l;
	unordered_map<string,list<Node>::iterator > m;

public:
	LRUCache(int maxSize);
	void insertKeyValue(string key,int value);
	int* getValue(string key);
	string mostRecentKey();

};

LRUCache::LRUCache(int maxSize){
	this->maxSize = maxSize > 1 ? maxSize : 1;
}

void LRUCache::insertKeyValue(string key,int value){
   auto it = m.find(key); 
   Node newNode = Node(key, value);
	if(it != m.end()){
		l.erase(it->second);
   	}
    else if(l.size() == maxSize){
		Node& lastNode = l.back();
		m.erase(lastNode.key);
		l.pop_back();
   	}
   l.push_front(newNode);
   m[key] = l.begin();
}

int* LRUCache::getValue(string key){
	auto it = m.find(key);
	if(it == m.end()){
		return nullptr;
	}
	l.splice(l.begin(), l, it->second);
	return &(it->second->value);


}

string LRUCache::mostRecentKey(){
	if(l.empty()){
		return "";
	}
	return l.begin()->key;
}

#endif