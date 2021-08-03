#include<iostream>
#include<map>
#include<vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string> &intputStr);
    string longestCommonPrefix(string &str1, string &str2);
};

string Solution::longestCommonPrefix(vector<string> &intputStr)
{
    int len = intputStr.size();
    string ansPrefix = intputStr[0];

    for(int i = 1; i < len; i++) {
        ansPrefix = longestCommonPrefix(ansPrefix, intputStr[i]);
    }
    return ansPrefix;
}

string Solution::longestCommonPrefix(string &str1, string &str2)
{
    int len    = min(str1.length(), str2.length());
    int ansIdx = 0;
    for(int i = 0; i < len; i++) {
        if(str1[i] != str2[i]) {
            break;
        }
        ansIdx++;
    }
    return str1.substr(0, ansIdx);
}

int main() {
    vector<string> inputStr;
    string line;
    getline(std::cin, line);
    std::istringstream iss(line);

    for(string s; iss >> s; inputStr.push_back(s)){};
}
