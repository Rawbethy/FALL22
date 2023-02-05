#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]) {
    std::vector<std::pair<std::string, int>> results;
    std::string inFile, line;
    int prev;
    inFile = argv[1];
    std::ifstream myfile(inFile);
    if(myfile.is_open()) {
        while(getline(myfile,line)) {
            prev = 0;
            for(int i = 0; i <= line.size(); i++) {
                if(line[i] >= 32 && line[i] <= 64 || line[i] == '\n' || line[i] == '\0') {
                    if(line[i-1] >= 32 && line[i-1] <= 64) {
                        prev = i + 1;
                        continue;
                    }
                    else {
                        std::string sub;
                        if(i == line.size()) {
                            sub = line.substr(prev, i-prev-1);
                        }
                        else {
                            sub = line.substr(prev, i-prev);
                        }
                        int size = sub.size();
                        char currChar[size];
                        strcpy(currChar, sub.c_str());
                        for(int j = 0; j < i-prev; j++) {
                            currChar[j] = tolower(currChar[j]);
                        }
                        std::string subStr(currChar);
                        bool isWord = false;
                        if(results.empty()) {
                            results.push_back(make_pair(subStr, 1));
                        }
                        else {
                            for(int j = 0; j < results.size(); j++) {
                                if(results[j].first == subStr) {
                                    results[j].second += 1;
                                    isWord = true;
                                    break;
                                }
                            }
                            if(isWord == false) {
                                results.push_back(make_pair(subStr, 1));
                            }
                        }
                    }
                    prev = i + 1;
                }
            }
        }
    }
    else {
        std::cout << "Error in opening text file" << std::endl;
        EXIT_FAILURE;
    }
    myfile.close();

    int max = results[0].second;
    int maxInd = 0;
    for(int i = 0; i < results.size(); i++) {
        if(max < results[i].second) {
            max = results[i].second;
            maxInd = i;
        }
    }
    std::ofstream outFile;
    outFile.open(argv[2]);
    outFile << results[maxInd].first << " " << results[maxInd].second << std::endl;
    outFile.close();

    return 0;
}