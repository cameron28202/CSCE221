#include <iostream>
#include <thread>
using namespace std;

void merge(int *arr, int start, int mid, int end){
    int firstLen = mid - start + 1;
    int secondLen = end - mid;

    // create sub arrays to eventually sort and merge together
    int leftArray[firstLen];
    int rightArray[secondLen];

    // fill leftarray
    for(int i = 0; i < firstLen; ++i){
        leftArray[i] = arr[start + i];
    }

    // fill rightarray
    for(int i = 0; i < secondLen; ++i){
        rightArray[i] = arr[mid + i + 1];
    }
    int i = 0; // first sub array ind
    int j = 0; // second sub array ind
    int k = start; // arr ind

    // compare left & right elements with eachother to merge
    while(i < firstLen && j < secondLen){
        if(leftArray[i] <= rightArray[j]){
            arr[k] = leftArray[i];
            ++i;
        }
        else{
            arr[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    //fill w remaining elements

    while(i < firstLen){
        arr[k] = leftArray[i];
        ++k;
        ++i;
    }

    while(j < secondLen){
        arr[k] = rightArray[j];
        ++j;
        ++k;
    }
}

void mergeSort(int *arr, int start, int end, int level) {
    if(start < end){
        int mid = start + (end - start) / 2;
        if(level > 0){
            thread leftThread(mergeSort, arr, start, mid, level-1);
            thread rightThread(mergeSort, arr, mid+1, end, level - 1);
            leftThread.join();
            rightThread.join();
        }
        else{
            mergeSort(arr, start, mid, level - 1);
            mergeSort(arr, mid+1, end, level - 1);
        }
        merge(arr, start, mid, end);
    }
}