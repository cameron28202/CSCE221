#include <iostream>
#include "SortedPriorityQueue.h"

using namespace std;

void countSort(int *arr, int exp, int n){
    int ans[n];
    int count[10] = {0};

    for(int i = 0; i < n; ++i){
        ++count[arr[i] / exp % 10];
    }
    for(int i = 1; i < 10; ++i){
        count[i] += count[i-1];
    }

    for(int i = n-1; i >= 0; --i){
        ans[count[arr[i] / exp % 10] - 1] = arr[i];
        --count[arr[i] / exp % 10];
    }

    for(int i = 0; i < n; ++i){
        arr[i] = ans[i];
    }
}

void radixSort(int *arr, int n) {
    int max = 0;
    for(int i = 0; i < n; ++i){
        if(arr[i] > max){
            max = arr[i];
        }
    }

    for(int i = 1; max / i > 0; i *= 10){
        countSort(arr, i, n);
    }
}


void insertionSort(int *arr, int n) {
    SortedPriorityQueue<int> pq;
    for(int i = 0; i < n; ++i){
        pq.pq_insert(arr[i]);
    }

    for(int i = 0; i < n; ++i){
        arr[i] = pq.pq_delete();
    }
}
