#include <iostream>
#include <queue>
using namespace std;

void bubbleSort(int *arr, int size){
    
    bool swapped = true;
    while(swapped){
        swapped = false;
        for(int i = 1; i < size; ++i){
            if(arr[i-1] > arr[i]){
                std::swap(arr[i-1], arr[i]);
                swapped = true;
            }
        }
    }
    
    
}

void heapSort(int *arr, int size){
    std::priority_queue<int> pq;
    for(int i = 0; i < size; ++i){
        pq.push(arr[i]);
    }
    for(int i = size - 1; i >= 0; --i){
        arr[i] = pq.top();
        pq.pop();
    }
}

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

void mergeSort(int *arr, int start, int end) {
    if(start < end){
        int mid = start + (end - start) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid+1, end);
        merge(arr, start, mid, end);
    }
}

int qsHelper(int *arr, int start, int end){
    // pivot as middle element
    int mid = start + (end-start)/2;
    int pivot = arr[mid];

    // store pivot at end
    std::swap(arr[mid], arr[end]);

    int i = start - 1;

    // sort elements before pivot
    for(int j = start; j < end; ++j){
        if(arr[j] < pivot){
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    // put pivot back in correct place
    std::swap(arr[i+1], arr[end]);
    return i + 1;
}

void quickSort(int *arr, int start, int end) {
    if(start < end){
        int ind = qsHelper(arr, start, end);
        quickSort(arr, start, ind-1);
        quickSort(arr, ind + 1, end);
    }
}


