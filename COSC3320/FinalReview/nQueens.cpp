#include <iostream>
#include <stdlib.h>
#include <vector>
bool isSafe(std::vector<std::vector<bool>> boolboard, int n, int row, int col) {
    // checking row
    for(int k = 0; k < n; k++) {
        if(k==row) {
            continue;
        }
        if(boolboard[row][k] == true) {
            return false;
        }
    }

    // checking upper diagonal to left
    for(int k = row-1; k >= 0; k--) {
        for(int l = col-1; l >= 0; l--) {
            if(boolboard[k][l] == true) {
                return false;
            }
        }
    }

    // checking lower diagonal to rleft
    for(int k = row+1; k < n; k++) {
        for(int l = col-1; l >= 0; l--) {
            if(boolboard[k][l] == true) {
                return false;
            }
        }
    }

    return true;
}

bool solveUtil(std::vector<std::vector<bool>> boolboard, int n, int col) {
    if(col >= n) {
        return true;
    }

    for(int i = 0; i < n; i++) {
        if(isSafe(boolboard, n, i, col) == true) {
            boolboard[i][col] = true;
            if(solveUtil(boolboard, n, col+1) == true) {
                return true;
            }
        }
        boolboard[i][col] = false;
    }
    return false;
}

std::vector<std::vector<std::string>> nQueens(int n) {
    std::vector<std::vector<bool>> boolboard;
    std::vector<std::vector<std::string>> board;
    for(int i = 0; i < n; i++) {
        boolboard.push_back(std::vector<bool> ());
        for(int j = 0; j < n; j++) {
            boolboard[i].push_back(false);
        }
    }

    bool validBoard = solveUtil(boolboard, 0, 0);
    if(validBoard == 1) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                std::cout << boolboard[i][j] << " ";
            }
            std::cout << std::endl;
        }
        return board;
    }
    else {
        return board;
    }
}

int main() {
    int n;
    std::cout << "Enter size of chess board: ";
    std::cin >> n;
    std::vector<std::vector<std::string>> ans = nQueens(n);
    return 0;
}