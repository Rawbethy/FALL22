#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    std::ifstream in;
    in.open("in.txt");
    if(!in.is_open()) {
        return 0;
    }
    std::string word;
    while(in >> word) {
        if((int)word[word.length()-1] >= 32 && (int)word[word.length()-1] <= 64) {
            word = word.substr(0, word.length()-1);
        }
        std::cout << word << std::endl;
    }
    return 0;
}