#include <iostream>
#include <stdio.h>

int greedy(int val, int denoms[], int size) {
    if(val == 0) {
        return 0;
    }
    else{
        for(int j = size - 1; j >= 0; j--) {
            if(denoms[j] <= val) {
                return 1 + greedy(val - denoms[j], denoms, size); 
            }
        }  
    }
    return -1;
}

int main() {
    int i, value;
    int denoms[] = {1,4,7,13,28,52,91,365};
    int s = sizeof(denoms)/sizeof(int);
    std::cout << "Enter a value: ";
    std::cin >> value;
    std::cout << "Minimum denominations using greedy algorithm: " << greedy(value, denoms, s) << std::endl;
    return 0;
}