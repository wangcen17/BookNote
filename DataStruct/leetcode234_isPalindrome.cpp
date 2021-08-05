#include<iostream>
#include<map>
#include<vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode* pHalfLinkNode = findHalfLinkNode(head);
        ListNode* pHalfAfterReverse = reverseLinkNode(pHalfLinkNode);

        while(pHalfAfterReverse->next) {
            if(pHalfAfterReverse->val != head->val) {
                return false;
            }
            pHalfAfterReverse = pHalfAfterReverse->next;
            head = head->next;
        }
        return true;
    }

    ListNode* findHalfLinkNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        //tips: be careful here, the should judeg fast->next rather than slow->next;
        while(fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* reverseLinkNode(ListNode* head) {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        cout << "do reverse " << endl;
        while(cur) {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        } 
        return pre;
    }

    void printListNode(ListNode* head) {
        ListNode* cur = head;
        while(cur) {
            //tips: attention to the order of -> next;
            std::cout << " : " << cur->val;
            cur = cur->next;
        }
        cout << "" << endl;
    }
};


int main()
{
    Solution S;
    ListNode* cur = new ListNode(0);
    ListNode* head  = cur;

    cout << "create link " << endl;
    for(int i = 0; i < 5; i++) {
        ListNode* newNode = new ListNode(i+2);
        cur->next = newNode;
        cur = newNode;
    }
    S.printListNode(head);
    cout << "begin reverse " << endl;
    ListNode* pNodeAfterReverse = S.reverseLinkNode(head);
    cout << "after reverse " << endl;
    S.printListNode(pNodeAfterReverse);

    getchar();
}
