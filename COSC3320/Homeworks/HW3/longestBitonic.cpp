#include <iostream>
#include <stdio.h>
#include <algorithm>

int longestBitonic(int arr[], int len) {
    int dpArrInc[len] = {1}, dpArrDec[len] = {1};
    std::fill_n(dpArrInc, len, 1);
    std::fill_n(dpArrDec, len, 1);
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < i; j++) {
            if(arr[j] < arr[i] && (1 + dpArrInc[j]) > dpArrInc[i]) {
                dpArrInc[i] = 1 + dpArrInc[j];
            }
        }
    }
    int max = 0;
    for(int i = len-1; i >= 0; i--) {
        for(int j = len-1; j > i; j--) {
            if(arr[j] < arr[i] && (1 + dpArrDec[j]) > dpArrDec[i]) {
                dpArrDec[i] = 1 + dpArrDec[j];
            }
        }
        max = std::max(max, dpArrInc[i] + dpArrDec[i] - 1);
    }
    return max;
}

int main() {
    int len;
    std::cin >> len;
    int arr[len];
    for(int i = 0; i < len; i++) {
        std::cin >> arr[i];
    }
    std::cout << longestBitonic(arr, len) << std::endl;
    return 0;
}