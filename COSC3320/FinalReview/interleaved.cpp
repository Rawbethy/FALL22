#include <iostream>
#include <stdlib.h>
#include <vector>

bool dfs(int i, int j, std::vector<std::vector<int>> dp, std::string s1, std::string s2, std::string s3) {
    if(i==s1.length() && j==s2.length()) {
        return 1;
    }

    if(dp[i][j] != -1) {
        return dp[i][j];
    }

    if((i < s1.length() && s3[i+j] == s1[i]) && (j < s2.length() && s3[i+j] == s2[j])) {
        bool x = dfs(i+1, j, dp, s1, s2, s3);
        bool y = dfs(i, j+1, dp, s1, s2, s3);

        dp[i][j] = x|y;
        return dp[i][j];
    }

    if(i < s1.length() && s3[i+j] == s1[i]) {
        bool x = dfs(i+1, j, dp, s1, s2, s3);
        dp[i][j] = x;
        return dp[i][j];
    }

    if(j < s2.length() && s3[i+j] == s2[j]) {
        bool x = dfs(i, j+1, dp, s1, s2, s3);
        dp[i][j] = x;
        return dp[i][j];
    }


    dp[i][j] = 0;
    return dp[i][j];
}

bool isInterleave(std::string s1, std::string s2, std::string s3) {
    int len1 = s1.length();
    int len2 = s2.length();
    int len3 = s3.length();

    if((len1+len2) < len3) {
        std::cout << "False" << std::endl;
        return false;
    }

    std::vector<std::vector<int>> dp;
    for(int i = 0; i < len1+1; i++) {
        dp.push_back(std::vector<int> ());
        for(int j = 0; j < len2+1; j++) {
            dp[i].push_back(-1);
        }
    }

    bool isInterleaved = dfs(0, 0, dp, s1, s2, s3);
    return isInterleaved;
}

int main() {
    std::string s1, s2, s3;
    std::cout << "Enter first string: ";
    std::cin >> s1;
    std::cout << "Enter second string: ";
    std::cin >> s2;
    std::cout << "Enter thrid string: ";
    std::cin >> s3;
    bool yes = isInterleave(s1, s2, s3);
    if(yes == 1) {
        std::cout << "true" << std::endl;
    }
    else {
        std::cout << "false" << std::endl;
    }
    return 0;
}