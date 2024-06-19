//#include <chrono>
#include "AbstractPriorityQueue.h"
#include "PriorityQueueHeap.h"
#include "UnsortedPriorityQueue.h"
#include "SortedPriorityQueue.h"
#include <iostream>
#include <vector>
#include <random>    
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
using namespace std::chrono;

int main() {
    auto start = high_resolution_clock::now();
    SortedPriorityQueue<int> arr = SortedPriorityQueue<int>();
    for(int i = 0; i < 100; ++i){
        arr.pq_insert(i);
    }

    for(int i = 0; i < 100; ++i){
        arr.pq_delete();
    }

    auto stop = high_resolution_clock::now();
    auto dur = duration_cast<microseconds>(stop - start);
    cout << dur.count() << endl;
    return 0;
}