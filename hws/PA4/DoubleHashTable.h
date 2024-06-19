#ifndef DOUBLEHASHING_H
#define DOUBLEHASHING_H

#include "AbstractHashTable.h"
#include <vector>

// Double hashing hash table class
class DoubleHashTable : public AbstractHashTable {
    private:
    // helper functions
    int secondHash(std::string s) const;
    std::vector<HashEntry> table;
    int prevPrime;
    void resizeAndRehash();

    public: 
    DoubleHashTable();
    ~DoubleHashTable(); 
    void insert(std::string key, int val); 
    int remove(std::string key); 
    int get(std::string key) const; 
    bool contains(std::string key) const;
};


///////////////////// TODO: FILL OUT THE FUNCTIONS /////////////////////

// constructor 
DoubleHashTable::DoubleHashTable(): AbstractHashTable() {
	prevPrime = findPrevPrime(capacity);
    table = std::vector<HashEntry>(capacity);
}

// destructor
DoubleHashTable::~DoubleHashTable() {
    capacity = 11;
    maxLoadFactor = .75;
    num_elements = 0;
    table = std::vector<HashEntry>(capacity);
}

// inserts the given string key
void DoubleHashTable::insert(std::string key, int val) {
    int ind = hash(key);
    int offset = secondHash(key);
    int origInd = ind;
    int firstDeletedInd = -1;
    bool foundSpot = false;
    do{
        // need to make sure we know if we have the same 
        // key already in the map. skip over deleted spots and store first deleted index.
        if(table.at(ind).key == key && !table.at(ind).DELETED){
            //cout << "key already exists, updating val" << endl;
            table.at(ind).val = val;
            table.at(ind).DELETED = false;
            table.at(ind).isFilled = true;
            foundSpot = true;
        }
        if(table.at(ind).DELETED && firstDeletedInd == -1){
            //cout << "found first deleted spot. storing ind " << endl;
            firstDeletedInd = ind;
        }
        if(!table.at(ind).isFilled && !table.at(ind).DELETED){
            if(firstDeletedInd != -1){
                //cout << "found empty spot, but inserting at first deleted spot" << endl;
                table.at(firstDeletedInd) = HashEntry(key, val);
            }
            else{
                //cout << "found empty spot. inserting there" << endl;
                table.at(ind) = HashEntry(key, val);
            }
            ++num_elements;
            foundSpot = true;
        }
        ind = (ind + offset) % capacity;
        
    } while(ind != origInd && !foundSpot);
    if(load_factor() > maxLoadFactor){
        resizeAndRehash();
    }
}

// removes the given key from the hash table - if the key is not in the list, throw an error
int DoubleHashTable::remove(std::string key) {
	int ind = hash(key);
    int offset = secondHash(key);
    int origInd = ind;
    do{
        if(table.at(ind).key == key && !table.at(ind).DELETED){
            table.at(ind).DELETED = true;
            table.at(ind).isFilled = false;
            --num_elements;
            return table.at(ind).val;
        }
        if(!table.at(ind).isFilled && !table.at(ind).DELETED){
            break;
        }
        ind = (ind + offset) % capacity;
    } while(ind != origInd);
    throw std::out_of_range("cant find");
}

// getter to obtain the value associated with the given key
int DoubleHashTable::get(std::string key) const {
	int ind = hash(key);
    int offset = secondHash(key);
    int origInd = ind;
    do{
        if(table.at(ind).key == key && !table.at(ind).DELETED && table.at(ind).isFilled){
            return table.at(ind).val;
        }
        if(!table.at(ind).isFilled && !table.at(ind).DELETED){
            break;
        }
        ind = (ind + offset) % capacity;
    } while(ind != origInd);
    throw std::out_of_range("cant find in get");
}

bool DoubleHashTable::contains(std::string key) const {
	int ind = hash(key);
    int offset = secondHash(key);
    int origInd = ind;
    do{
        if(table.at(ind).key == key && !table.at(ind).DELETED){
            return true;
        }
        if(!table.at(ind).isFilled && !table.at(ind).DELETED){
            return false;
        }
        ind = (ind + offset) % capacity;
    }  while(ind != origInd);
    return false;
}

void DoubleHashTable::resizeAndRehash() {
    int oldCap = capacity;
    capacity = findNextPrime(2 * capacity);
    std::vector<HashEntry> oldTable = table;
    table = std::vector<HashEntry>(capacity);
    num_elements = 0;

    for (int i = 0; i < oldCap; ++i) {
        if (oldTable[i].isFilled && !oldTable[i].DELETED) {
            insert(oldTable[i].key, oldTable[i].val);
        }
    }
}

// helper functions 
int DoubleHashTable::secondHash(std::string s) const {
	int hashVal = 0;
    for (char ch : s) {
        hashVal = 31 * hashVal + ch;
    }
    return prevPrime - (hashVal % prevPrime);
}

#endif