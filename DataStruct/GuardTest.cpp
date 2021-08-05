#include<iostream>
#include<map>
#include<vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include<time.h>
using namespace std;

enum FindType {
    Defaule,
    AddGuard,
    MAX
};

class GuardTest {
public:
    GuardTest() = default;
    ~GuardTest(){};
    GuardTest(const GuardTest &obj);
    GuardTest& operator = (const GuardTest &obj);

    int findTarget(vector<int> &targets, const int target, FindType type){
        int ansIdx = -1;
        switch (type)
        {
        case FindType::Defaule:
            ansIdx = findTargetDefault(targets, target);
            break;
        case FindType::AddGuard:

            break;
        default:
            break;
        }
        return ansIdx;
    }

    int findTargetDefault(vector<int> &targets, const int target) {
        int idx = 0;
        for(idx; idx < targets.size(); idx++) {
            if(target == targets[idx]) {
                return idx;
            }
        }
        return -1;
    }

    int findTargetWithGuard(vector<int> &targets, int target) {
        int lastValue = targets.back();
        int len       = targets.size();
        int idx       = 0;

        if(lastValue == target) {
            return len - 1;
        }
        targets[len-1] = target;

        //耗时的节约在这里，没有了比较的过程，这个改动就是为了举例子，实际操作不美观
        while(targets[idx] != target) {
            idx++;
        }

        targets[len-1] = lastValue;

        if(idx == len - 1) return -1;
        return idx;
    }
};


int main()
{
    GuardTest G;
    vector<int> testInput;
    clock_t start,end;//数据类型是clock_t，需要头文件#include<time.h>

    for(int i = 0; i < 1000000; i++) {
        int num = rand()%100;
        testInput.push_back(num);
    }
    testInput.push_back(2008);
    testInput.push_back(99);

    start = clock();
    G.findTarget(testInput, 2008, FindType::Defaule);
    end = clock();

    cout << "time cost is " << (double)(end-start)/CLOCKS_PER_SEC << endl;

    start = clock();
    G.findTarget(testInput, 2008, FindType::AddGuard);
    end = clock();

    cout << "time cost is " << (double)(end-start)/CLOCKS_PER_SEC << endl;//单位是/s
}
