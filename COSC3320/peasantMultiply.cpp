#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>

int prod = 0;

int peasantMultiply(int x, int y) {
    if(x==0) {
        return 0;
    }
    else {
        if(x%2 != 0) {
            prod = prod + y;
        }
        x = floor(x/2);
        y = y+y;
        return prod + peasantMultiply(x,y);
    }
}

int main() {
    int x, y;
    std::cout << "Enter x: ";
    std::cin >> x;
    std::cout << "Enter y: ";
    std::cin >> y;

    std::cout << "The result is " << peasantMultiply(x,y) << std::endl;
    return 0;
}