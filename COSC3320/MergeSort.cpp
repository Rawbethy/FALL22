#include <iostream>
#include <stdlib.h>
#include <stdio.h>

void merge(int arr[], int begin, int mid, int end) {
    
    int sizeleft = mid - begin + 1;
    int sizeright = end - mid;

    int leftArray[sizeleft];
    int rightArray[sizeright];

    for(int i = 0; i < sizeleft; i++) {
        leftArray[i] = arr[begin + i];
    }
    for(int i = 0; i < sizeright; i++) {
        rightArray[i] = arr[mid+1+i];
    }

    int leftind = 0;
    int rightind = 0;
    int mergeind = begin;

    while(leftind < sizeleft && rightind < sizeright) {
        if(leftArray[leftind] <= rightArray[rightind]) {
            arr[mergeind] = leftArray[leftind];
            leftind++;
        }
        else {
            arr[mergeind] = rightArray[rightind];
            rightind++;
        }
        mergeind++;
    }

    while(leftind < sizeleft) {
        arr[mergeind] = leftArray[leftind];
        mergeind++;
        leftind++;
    }

    while(rightind < sizeright) {
        arr[mergeind] = rightArray[rightind];
        mergeind++;
        rightind++;
    }
}

void mergesort(int arr[], int begin, int end) {
    if(begin >= end) {
        return;
    }
    int mid = begin + (end - begin)/2;
    mergesort(arr, begin, mid);
    mergesort(arr, mid + 1, end);
    merge(arr, begin, mid, end);
}


int main() {
    int arr[] = {53,23,10,23,54,73,12,90,4,20,31,74,34,103,122,90};
    int size = sizeof(arr)/sizeof(arr[0]);
    std::cout << "Array before MergeSort called: " << std::endl;
    for(int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    mergesort(arr, 0, size-1);
    
    std::cout << std::endl;
    std::cout << "Array after MergeSort called: " << std::endl;
    for(int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    return 0;
}