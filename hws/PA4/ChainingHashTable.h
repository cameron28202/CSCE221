#ifndef CHAINING_H
#define CHAINING_H

#include "AbstractHashTable.h"
#include <vector>
#include <list>


// Chaining hash table class
class ChainingHashTable: public AbstractHashTable {
    private:
    std::vector<std::list<HashEntry>> table;
    void resizeAndRehash();

    public: 
    ChainingHashTable();
    ~ChainingHashTable(); 
    void insert(std::string key, const int val); 
    int remove(std::string key); 
    int get(std::string key) const;
    bool contains(std::string key) const;
};


///////////////////// TODO: FILL OUT THE FUNCTIONS /////////////////////

// constructor
ChainingHashTable::ChainingHashTable(): AbstractHashTable(), table(capacity) {}

// destructor
ChainingHashTable::~ChainingHashTable() {
   capacity = 11;
   maxLoadFactor = .75;
   num_elements = 0;
   std::vector<std::list<HashEntry>> table(capacity);
}

// inserts the given string key
void ChainingHashTable::insert(std::string key, int val) {
	
    int ind = hash(key);
    auto& bucket = table.at(ind);
    for(auto it = bucket.begin(); it != bucket.end(); ++it){
        if(it->key == key){
            it->val = val;
            return;
        }
    }
    bucket.emplace_back(key, val);
    ++num_elements;
    if(load_factor() > maxLoadFactor){
        resizeAndRehash();
    }
}

// removes the given key from the hash table - if the key is not in the list, throw an error
int ChainingHashTable::remove(std::string key) {
	int ind = hash(key);
    auto& bucket = table.at(ind);
    auto it = bucket.begin();
    
    while(it != bucket.end()){
        if(it->key == key){
            int val = it->val;
            bucket.erase(it);
            --num_elements;
            return val;
        }
        ++it;
    }
    throw std::out_of_range("no key bro");
}

// getter to obtain the value associated with the given key
int ChainingHashTable::get(std::string key) const {
	int ind = hash(key);
    auto& bucket = table.at(ind);
    auto it = bucket.begin();
    while(it != bucket.end()){
        if(it->key == key){
            return it->val;
        }
        ++it;
    }
    throw std::out_of_range("no key bro");

}

bool ChainingHashTable::contains(const std::string key) const {
	int ind = hash(key);
    auto& bucket = table.at(ind);
    auto it = bucket.begin();
    while(it != bucket.end()){
        if(it->key == key){
            return true;
        }
        ++it;
    }
    return false;
}

void ChainingHashTable::resizeAndRehash() {
    int oldCap = capacity;
    capacity = findNextPrime(capacity * 2);

   std::vector<std::list<HashEntry>> newTable(capacity);
   for(int i = 0; i < oldCap; ++i){
    for(auto& item : table[i]){
        int ind = hash(item.key);
        newTable[ind].push_back(item);
    }
   }
   table = std::move(newTable);
}

#endif