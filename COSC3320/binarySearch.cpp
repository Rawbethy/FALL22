#include <iostream>
#include <stdio.h>

int findX(int arr[], int x, int low, int high) {
    int mid = low + (high-low)/2;
    if(high >= low) {
        if(x == arr[mid]) {
            return arr[mid];
        }
        else if(x > arr[mid]) {
            return findX(arr, x, mid + 1, high);
        }
        else if(x < arr[mid]) {
            return findX(arr, x, low, mid - 1);
        }
    }
    return -1;
}

int main() {
    int arr[] = {1,3,5,9,11,18,23,29,34,48,53,58,61};
    int find = 17;
    int low = 0, high = (sizeof(arr)/sizeof(arr[0]))-1;
    int ans = findX(arr, find, low, high-1);
    if(ans == -1) {
        std::cout << "The number " << find << " is not in the array" << std::endl;
    }
    else{
        std::cout << find << " found in the array" << std::endl;
    }
    return 0;
}