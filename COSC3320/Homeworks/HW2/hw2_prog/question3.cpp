#include <stdio.h>
#include <iostream>

int total = 0;

int minTotal(int arr[], int rowNum[], int n) {
    int min = 100000;
    int ind;
    for(int i = 0; i < n; i++) {
        if(arr[i] <= min) {
            min = arr[i];
            ind = rowNum[i];
        }
    }
    total += min;
    return ind;
}

int minIndex(int arr[], int n) {
    int min = 10000;
    int minInd;
    for(int i = 0; i < n; i++) {
        if(arr[i] <= min) {
            min = arr[i];
            minInd = i;
        }
    } 
    total += min;
    return minInd;
}

int main() {
    int r, c;
    std::cin >> r >> c;
    int matrix[r][c], firstC[r];
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            std::cin >> matrix[i][j];
        }
    }

    for(int i = 0; i < r; i++) {
        firstC[i] = matrix[i][0];
    }

    int path[c];
    int opt[3], rind[3];
    path[0] = minIndex(firstC, r);
    for(int i = 1; i < c; i++) {
        for(int j = 0; j < 3; j++) {
            int curRow;
            if(path[i-1] == 0 && j == 0) {
                curRow = r-1;
                opt[j] = matrix[curRow][i];
                rind[j] = curRow;
                continue;
            }
            if(path[i-1] == r-1 && j == 2) {
                curRow = 0;
                opt[j] = matrix[curRow][i];
                rind[j] = curRow;
                continue;
            }
            curRow = (path[i-1] - 1) + j;
            opt[j] = matrix[curRow][i]; 
            rind[j] = curRow;
        }
        int row = minTotal(opt, rind, 3);
        path[i] = row;
    }
    std::cout << total << std::endl;
    return 0;
}