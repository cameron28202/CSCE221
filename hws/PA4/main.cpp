#include <iostream>
#include <chrono>
#include "ChainingHashTable.h"
#include "DoubleHashTable.h"
#include "ProbingHashTable.h" 
using namespace std::chrono;

int main() {
    auto start = high_resolution_clock::now();
    DoubleHashTable aht;
    for(int i = 0; i < 1000000; ++i){
        aht.insert(std::to_string(i), i);
    }

    auto stop = high_resolution_clock::now();
    auto dur = duration_cast<microseconds>(stop - start);
    cout << dur.count() << endl;
    return 0;
}
