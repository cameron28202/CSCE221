#include "sort.cpp"

int main() {
    int* arr = new int[4];
    arr[0] = 2;
    arr[1] = 8;
    arr[2] = 4;
    arr[3] = 9;
    arr[4] = 3;

    insertionSort(arr, 5);

    for(int i = 0; i < 5; ++i){
        cout << arr[i];
    }
}