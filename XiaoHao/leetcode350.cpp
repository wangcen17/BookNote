#include<iostream>
#include<map>
#include<vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
using namespace std;

enum FixType {
    TwoPointer,
};

class Solution {
public:
    Solution() = default;
    ~Solution(){};
    Solution(const Solution &obj);
    Solution& operator = (const Solution &obj);

    /*
        时间复杂度：O(m+n)O(m+n)O(m+n);
        空间复杂度：O(min⁡(m,n))O(\min(m,n))O(min(m,n))-哈希表
    */
    vector<int> intersect(vector<int> num1, vector<int>num2) {
        // tips: add to decrease the counter time and space;
        if(num1.size() > num2.size()) {
            return intersect(num2, num1);
        }
        unordered_map<int, int> counter;
        vector<int>             ans;   
        for(int num : num1) {
            counter[num]++;
        }

        for(int num : num2) {
            if(counter[num] > 0) {
                counter[num]--;
                ans.push_back(num);
            }
        }
        printVector(ans);
        return ans;
    }

    vector<int> intersect(vector<int> &num1, vector<int> &num2, FixType type) {
        switch (type)
        {
        case FixType::TwoPointer:
            return TwoPointerWay(num1, num2);
            break;
        
        default:
            return intersect(num1, num2);
            break;
        }
    }
    
    /*
        时间复杂度：O(mlog⁡m+nlog⁡n)O(m \log m+n \log n)O(mlogm+nlogn)
        空间复杂度：O(min⁡(m,n))O(\min(m,n))O(min(m,n))
    */
    vector<int> TwoPointerWay(vector<int> &num1, vector<int> &num2) {
        vector<int> ans;
        int idx1 = 0, idx2 = 0;
        sort(num1.begin(), num1.end());
        sort(num2.begin(), num2.end());

        while(idx1 < num1.size() && idx2 < num2.size()) {
            if(num1[idx1] < num2[idx2]) {
                idx1++;
            } else if(num1[idx1] > num2[idx2]) {
                idx2++;
            } else {
                idx1++;
                idx2++;
                ans.push_back(num1[idx1]);
            }
        }
        return ans;
    }

    template<typename T>
    void printVector(vector<T> &input) {
        for(auto i : input) {
            cout << " " << i;
        }
        cout << " " << endl;
    }
};

int main()
{
    Solution S;

    vector<int> input1, input2;

    cout << "please input vector1 " << endl; 
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    for(int in1; iss >> in1; input1.push_back(in1)){};

    S.printVector(input1);

    cout << "please input vector1 " << endl; 
    std::getline(std::cin, line);
    std::istringstream iss2(line);
    for(int in2; iss2 >> in2; input2.push_back(in2)){};
    S.printVector(input2);

    S.intersect(input1, input2);

    getchar();
    return 0;   
};
