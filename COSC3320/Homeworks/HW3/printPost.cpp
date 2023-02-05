#include <iostream>
#include <stdio.h>

void printPost(int pre[], int in[], int len) {

    // Since the root of the current pre-order tree is always the first element of the pre-order traversal, we will make an algorithm
    // that will find the current root of the current pre-order tree. If the current root is 0 in the corresponding in-order traversal tree,
    // there is no left child. If the current root is the last element of the correspoding in-order tree, then there is no 
    // right child. We find the root and recursively print all left child nodes of all roots, then we do the same but for right
    // children. Finally, we print the current root of the pre order tree since there are no more children to iterate through.
    int currRoot = -1;
    for(int i = 0; i < len; i++) {
        if(in[i] == pre[0]) {
            currRoot = i;
        }
    }
    if(currRoot == -1) {
        std::cout << "Root not found" << std::endl;
        exit(0);
    }

    if(currRoot != 0) {
        printPost(pre + 1, in, currRoot);
    }

    if(currRoot != len-1) {
        printPost(pre + currRoot + 1, in + currRoot + 1, len - currRoot - 1);
    }

    std::cout << pre[0] << " ";
}

int main() {
    int len;
    std::cin >> len;
    int pre[len], in[len];
    for(int i = 0; i < len; i ++) {
        std::cin >> pre[i];
    }
    for(int i = 0; i < len; i++) {
        std::cin >> in[i];
    }
    printPost(pre, in, len);
    std::cout << std::endl;
    return 0;
}