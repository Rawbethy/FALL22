#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]) {

    std::vector<std::pair<std::string, int>> results;
    std::string inFile, line, current, argstring = argv[1];
    std::vector<std::string> args;
    int size = argstring.size();                                                                                                            //These few lines will essentially split the single argument string into two distinctive string values that will
    char argchar[size];                                                                                                                     //be used as the text file names that will be used as the input and output
    strcpy(argchar, argstring.c_str());
    int start = 0;
    for(int i = 0; i < size; i++) {
        if((int)argchar[i] == 61) {
            start = i + 1;
        }
        else if((int)argchar[i] == 59 || i == size-1) {
            if(i == size-1) {
                current = argstring.substr(start,i-start+1);
                args.push_back(current);
            }
            else {
                current = argstring.substr(start,i-start);
                args.push_back(current);
            }
        }
    }
    if(args.size() > 2) {
        std::cout << "ERROR: Too many arguments. Input should be in the format of ./filename \"in=input.txt;out=out.txt\"" << std::endl;
        abort;
    }
    else if(args.size() < 2) {
        std::cout << "ERROR: Too few arguments. Input should be in the format of ./filename \"in=input.txt;out=out.txt\"" << std::endl;
        abort;
    }
    for(int i = 0; i < args.size(); i++) {
        int size = args[i].size();
        if(args[i].substr(size-4, 4) != ".txt") {
            std::cout << "ERROR: Argument " << i << " needs to end in the extension .txt" << std::endl;
            abort;
        }
    }
    inFile = args[0];
    int prev;
    std::ifstream myfile(inFile);                                                                               //Create in file stream from argument 1 that was passed during execution
    if(myfile.is_open()) {
        while(getline(myfile,line)) {                                                                           //I will be using a while loop for each line of the input file then use a for loop to iterate through each character of the
            prev = 0;                                                                                           //line taken from the while loop
            for(int i = 0; i <= line.size(); i++) {
                if(line[i] >= 32 && line[i] <= 64 || line[i] == '\n' || line[i] == '\0') {                      //Here, we will check to see if the character in the line is a delimiter or special character, if it is
                    if(line[i-1] >= 32 && line[i-1] <= 64) {                                                    //THIS loop will check to see if the character before that was a delimiter. If both are delimiters, we index previous to  
                        prev = i + 1;                                                                           //i + 1 for the beginning of the next word. Prev is used for the beginning of a possible word
                        continue;
                    }
                    else {
                        std::string sub;
                        if(i == line.size()) {                                                                  //This if statement checks to see if i is equal to the size of the line, if it is, the substr function will be of length
                            sub = line.substr(prev, i-prev-1);                                                  //i-prev-1. Otherwise, the length will always be i-prev
                        }
                        else {
                            sub = line.substr(prev, i-prev);
                        }
                        int size = sub.size();
                        char currChar[size];                                                                    //I will make a char array to hold the substring of a word so that we can use a function to make all letters lowercase
                        strcpy(currChar, sub.c_str());
                        for(int j = 0; j < i-prev; j++) {                                                       //This for loop will iterate through the now char array to make all letters lowercase to provide uniformity if there are
                            currChar[j] = tolower(currChar[j]);                                                 //capitalized words given.
                        }
                        std::string subStr(currChar);
                        bool isWord = false;                                                                    //This boolean variable will check if the word is already a part of the results vector already or not.
                        if(results.empty()) {
                            results.push_back(make_pair(subStr, 1));                                    
                        }
                        else {
                            for(int j = 0; j <= results.size(); j++) {                                          //Searches if the substring is a vector variable. If it is a vector variable, we will increase the second parameter of the
                                if(results[j].first == subStr) {                                                //vector by 1 and set isWord to true
                                    results[j].second += 1;
                                    isWord = true;
                                    break;
                                }
                            }
                            if(isWord == false) {                                                               //If the word is not a part of the vector (isWord = false), push that substring to the vector and intialize the second parameter
                                results.push_back(make_pair(subStr, 1));                                        //to 1 since this is the first time the word has appeared.
                            }
                        }
                    }
                    prev = i + 1;                                                                               //Iterate prev to make it the possible beginning of the next word
                }
            }
        }
    }
    else {
        std::cout << "Error in opening text file" << std::endl;                                                 //Error if .open() is not working
        EXIT_FAILURE;
    }

    int max = results[0].second;                                                                                    //Initialize a variable max to the first vector elements frequency and initialize an int varialbe maxInd to store the
    int maxInd = 0;                                                                                                 //index of the max frequency vector element
    for(int i = 0; i < results.size(); i++) {                                                                       //For loop to see which results appears the most in the inpout text file
        if(max < results[i].second) {       
            max = results[i].second;
            maxInd = i;
        }
    }

    std::ofstream outFile;                                                                                          //Create an output file that will print out the word and the frequency of that word from the input text file
    outFile.open(args[1]);
    outFile << results[maxInd].first << " " << results[maxInd].second << std::endl;
    outFile.close();
    return 0;
}