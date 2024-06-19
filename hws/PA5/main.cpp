#include "sort.cpp"
#include <chrono>
#include <random>
#include <iostream>
using namespace std::chrono;

int main(){
    auto start = high_resolution_clock::now();
    int* arr = new int[1000];
    std::random_device rd;
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

    // Define the range [1, 10]
    std::uniform_int_distribution<> distrib(1, 10000);

    // Generate and print a random number
    for(int i = 0; i < 1000; ++i){
        arr[i] = distrib(gen);
    }

    quickSort(arr, 0, 999);

    auto stop = high_resolution_clock::now();
    auto dur = duration_cast<microseconds>(stop - start);
    std::cout << dur.count() << endl;
    return 0;
}
