#ifndef HASH_H
#define HASH_H

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>

using namespace std;

class AbstractHashTable {
	protected:
		struct HashEntry {
			string key;
			int val;
			bool isFilled;
			bool DELETED;

			HashEntry() {
				isFilled = false;
				key = "";
				val = 0;
				DELETED = false;
			};

			HashEntry(std::string word, int value) {
				key = word;
				val = value;
				isFilled = true;
				DELETED = false;
			}
		};
		int capacity;
		int num_elements;
		float maxLoadFactor;
		// helper functions
		int hash(std::string s) const; 
		int findNextPrime(int n) const;
		int findPrevPrime(int n) const;
		bool isPrime(int n) const;
		float load_factor() const;
		virtual void resizeAndRehash() = 0;
		
	public: 
		AbstractHashTable();
		virtual ~AbstractHashTable() {}; 
		virtual void insert(std::string key, int val) = 0; 
		virtual int remove(std::string key) = 0; 
		virtual int get(std::string key) const = 0; 
		virtual bool contains(std::string key) const = 0;
		int getSize() const;
};


AbstractHashTable::AbstractHashTable() : capacity(11), num_elements(0), maxLoadFactor(.75) {}

// hash function to determine index where string key goes, as mentioned in the instructions
int AbstractHashTable::hash(std::string s) const {
	unsigned long hash = 0;
	int c = 31; 
	for(int i = 0; i < s.length(); ++i){
		hash = c * hash + static_cast<unsigned long>(s[i]);
	}
	return hash % capacity;
	
}

int AbstractHashTable::getSize() const {
	return num_elements;
}

float AbstractHashTable::load_factor() const {
	return static_cast<float>(num_elements) / capacity;
}

int AbstractHashTable::findNextPrime(int n) const {
	int num = n + 1;
	while(!isPrime(num)){
		++num;
	}
	return num;
}

int AbstractHashTable::findPrevPrime(int n) const {
    if (n <= 2) return 2;
    int prime = n;
    bool found = false;
    while (!found) {
        prime--;
        if (isPrime(prime)){
            found = true;
		}
    }

    return prime;
}

// Function to check if a number is prime
bool AbstractHashTable::isPrime(int n) const {
	if(n == 0 || n == 1){
		return false;
	}
	for(int i = 2; i <= n/2; ++i){
		if(n % i == 0){
			return false;
		}
	}
	return true;
}

#endif