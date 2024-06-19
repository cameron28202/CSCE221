#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "AbstractHashTable.h"
#include <vector>

// Linear probing hash table class
class ProbingHashTable : public AbstractHashTable {
    private:
    std::vector<HashEntry> table;
    void resizeAndRehash();
    
    public: 
    ProbingHashTable();
    ~ProbingHashTable(); 
    void insert(std::string key, int val); 
    int remove(std::string key); 
    int get(std::string key) const; 
    bool contains(std::string key) const;
};

///////////////////// TODO: FILL OUT THE FUNCTIONS /////////////////////

// constructor 
ProbingHashTable::ProbingHashTable(): AbstractHashTable(), table(capacity){
}

// destructor
ProbingHashTable::~ProbingHashTable() {
    capacity = 11;
    maxLoadFactor = .75;
    num_elements = 0;
    table = std::vector<HashEntry>(capacity);
}

// inserts the given string key
void ProbingHashTable::insert(std::string key, int val) {

	int ind = hash(key);
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
        ind = (ind + 1) % capacity;
        
    } while(ind != origInd && !foundSpot);
    if(load_factor() > maxLoadFactor){
        resizeAndRehash();
    }
}

// removes the given key from the hash table - if the key is not in the list, throw an error
int ProbingHashTable::remove(std::string key){
	int ind = hash(key);
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
        ind = (ind + 1) % capacity;
    } while(ind != origInd);
    throw std::out_of_range("cant find");
}

// getter to obtain the value associated with the given key
int ProbingHashTable::get(std::string key) const {
	int ind = hash(key);
    int origInd = ind;
    do{
        if(table.at(ind).key == key && !table.at(ind).DELETED && table.at(ind).isFilled){
            return table.at(ind).val;
        }
        if(!table.at(ind).isFilled && !table.at(ind).DELETED){
            break;
        }
        ind = (ind + 1) % capacity;
    } while(ind != origInd);
    throw std::out_of_range("cant find in get");
}

bool ProbingHashTable::contains(std::string key) const {
	int ind = hash(key);
    int origInd = ind;
    do{
        if(table.at(ind).key == key && !table.at(ind).DELETED){
            return true;
        }
        if(!table.at(ind).isFilled && !table.at(ind).DELETED){
            return false;
        }
        ind = (ind + 1) % capacity;
    }  while(ind != origInd);
    return false;
}

void ProbingHashTable::resizeAndRehash(){
    //cout << "resizing and rehashing" << endl;
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

#endif