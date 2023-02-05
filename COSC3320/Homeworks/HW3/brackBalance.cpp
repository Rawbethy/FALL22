#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <vector>

int isBalanced(std::string inString) {
    int len = inString.length();
    std::vector<int> longestBal; 
    int currBal = 0;
    std::stack<char> symStack;
    for(int i = 0; i < len; i++) {
        if(inString[i] == '(' || inString[i] == '{' || inString[i] == '[') {
            symStack.push(inString[i]);
            currBal = 0;
            continue;
        }
        if(inString[i] == ')') {
            if(!symStack.empty() && symStack.top() == '(') {
                symStack.pop();
                currBal += 1;
            }
            else {
                longestBal.push_back(currBal);
                currBal = 0;
            }
            continue;
        }
        if(inString[i] == '}') {
            if(!symStack.empty() && symStack.top() == '{') {
                symStack.pop();
                currBal += 1;
            }
            else {
                longestBal.push_back(currBal);
                currBal = 0;
            }
            continue;
        }
        if(inString[i] == ']') {
            if(!symStack.empty() && symStack.top() == '[') {
                symStack.pop();
                currBal += 1;
            }
            else {
                longestBal.push_back(currBal);
                currBal = 0;
            }
            continue;
        }
    }
    longestBal.push_back(currBal);
    int largest = 0;
    for(int i = 0; i < longestBal.size(); i++) {
        if(longestBal[i] > largest) {
            largest = longestBal[i];
        }
    }
    return largest*2;
}


int main() {
    std::string inString;
    std::cout << "Enter a string of brackets: ";
    std::cin >> inString;
    std::cout << "The longest balanced string of " << inString << " is " << isBalanced(inString) << std::endl;
    return 0;
}