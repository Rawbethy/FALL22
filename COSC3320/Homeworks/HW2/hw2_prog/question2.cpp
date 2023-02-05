#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
    int n;
    std::cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }
    int max = 0;
    int curInd = 0;
    for(int i = 1; i < n; i++) {
        if(arr[i] < arr[curInd]) {
            curInd = i;
            continue;
        }
        if(curInd < i && (arr[i] - arr[curInd]) > max) {
            max = arr[i] - arr[curInd];
        }
    }
    
    

    std::cout << max << std::endl;

    return 0;
};