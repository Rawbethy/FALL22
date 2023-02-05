#include <iostream>
#include <stdio.h>
#include <vector>

int n;
int min;
std::vector<int> v;
std::vector<int> ans;

void backtracking(int k) {
    if(v.size() >= min) {
        return;
    }
    if(k == n) {
        if(v.size() < min) {
            min = v.size();
            ans.clear();
            for(int i = 0; i < v.size(); i++) {
                ans.push_back(v[i]);
            }
        }
    }

    for(int i = v.size() -1; i >= 0; i--) {
        if(k + v[i] <= n) {
            v.push_back(k + v[i]);
            backtracking(k + v[i]);
            v.pop_back();
        }
    }
}


int main() {
    std::cout << "Enter a number: ";
    std::cin >> n;
    min = n;
    v.push_back(1);
    backtracking(1);
    for(int i = 0; i < ans.size(); i++) {
        std::cout << ans[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}