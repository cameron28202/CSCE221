#include <iostream>
using namespace std;
#include "AbstractStack.h"
#include "StackArrayDouble.h"
#include "StackArrayLinear.h"
#include "StackLinkedList.h"
#include <chrono>
using namespace std::chrono;

int main() {
    auto start = high_resolution_clock::now();
    StackArrayDouble<int> arr = StackArrayDouble<int>();
    for(int i = 0; i < 10000000; ++i){
        arr.push(i);
    }

    auto stop = high_resolution_clock::now();
    auto dur = duration_cast<microseconds>(stop - start);
    cout << dur.count() << endl;
    return 0;
}