#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/* This is the insertion sort sorting algorithm, it is a run time of O(n^2) because there is a nested for loop in the program.
 This means that the worst case scenario will result in a runtime of n^2 vice versa to a faster sorting algorithm like linear O(n). 
 This is examples wrost-case scenario will always be O(n^2) but depending on the inputs from the users, each may take more comparisons 
 than another depending on how many elements are entered into the array. */

void printArr(int arr[], int size) {
    for(int i = 0; i < size; i++) {
        std::cout << arr[i];
    }
    std::cout << std::endl;
}

int* insertionSort(int inArr[], int size) {
    for(int i = 1; i < size; i++) {
        int current = inArr[i];
        int j = i - 1;
        while(j > -1 && current < inArr[j]) {
            inArr[j+1] = inArr[j];
            j--;
        }
        inArr[j+1] = current;
    }
    return inArr;
}
int main() {

    int size;
    std::cout << "How many elements in array: ";
    std::cin >> size;
    std::cout << "Enter the elements seperated by a space: ";
    int arr[size];
    for(int i = 0; i < size; i++) {
        std::cin >> arr[i];
    }
    int* res = insertionSort(arr, size);
    for(int i = 0; i < size; i++) {
        std::cout << res[i];
    }
    std::cout << std::endl;

}