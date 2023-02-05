#include <iostream>
#include <stdio.h>
#include <algorithm>

int findOscSeq(int arr[], int len) {
    int longestSeq = 1;
    int dpArr[len][2] = {1};
    for(int i = 0; i < len; i++) {
        for(int j = i-1; j >= 0; j--) {
            if(i%2 == 0 && arr[j] < arr[i]) {
                dpArr[i][0] = std::max(dpArr[j][1]+1,dpArr[i][0]);
            }
            if(i%2 == 0 && arr[j] > arr[i]) {
                dpArr[i][1] = std::max(dpArr[j][0]+1,dpArr[i][1]);
            }
            if(i%2 != 0 && arr[j] < arr[i]) {
                dpArr[i][0] = std::max(dpArr[j][1]+1,dpArr[i][0]);
            }
            if(i%2 != 0 && arr[j] > arr[i]) {
                dpArr[i][1] = std::max(dpArr[j][0]+1,dpArr[i][1]);
            }
        }
        longestSeq = std::max(longestSeq, std::max(dpArr[i][1],dpArr[i][0]));
    }
    return longestSeq + 1;
}

int main() {
    int len;
    std::cout << "Enter size of array: ";
    std::cin >> len;
    int arr[len];
    for(int i = 0; i < len; i++) {
        std::cin >> arr[i];
    }
    int longSeq = findOscSeq(arr, len);
    std::cout << "Longest oscilating sequence is " << longSeq << std::endl;
}