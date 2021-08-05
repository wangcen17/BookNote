#include<iostream>
#include<map>
#include<vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <stack>
#include<time.h>
using namespace std;

/*
    LeetCode: 206 141 21 19 876
*/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class LinkTest {
public:
    LinkTest(const LinkTest &obj);
    LinkTest& operator = (const LinkTest &obj);
    
    ListNode* reverseSingleLink(ListNode* head);
    bool      hasCycle(ListNode* head);
    bool      hasCycleBySet(ListNode* head);
    ListNode* mergeTwoLink(ListNode* L1, ListNode* L2);
    ListNode* deleteNthFromEnd(ListNode* head, int n);
    ListNode* deleteNthFromEndByStack(ListNode* head, int n);
    ListNode* findMiddleNode(ListNode* head);
};

ListNode* LinkTest::reverseSingleLink(ListNode* head) {
    ListNode* pre = nullptr;
    ListNode* cur = head;

    while(cur) {
        ListNode* tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
    }

    return pre;
}

bool LinkTest::hasCycle(ListNode* head) {
    if(head == nullptr || head->next == nullptr) return false;

    ListNode* slow = head;
    ListNode* fast = head->next;
    //to make sure that the while can work - do fast = head->next
    while(slow != fast) {
        if(fast == nullptr || fast->next == nullptr) {
            return false;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return true;
}

// judge has cycle or not by add address in to set
bool LinkTest::hasCycleBySet(ListNode* head) {
    unordered_set<ListNode*> checker;

    while(head) {
        if(checker.count(head)){
            return true;
        }
        checker.insert(head);
        head = head->next;
    }
    return false;
}

ListNode* LinkTest::mergeTwoLink(ListNode* L1, ListNode* L2) {
    ListNode* head = new ListNode();
    ListNode* guard = head;

    while(L1 != nullptr && L2 != nullptr) {
        if(L1->val < L2->val) {
            guard->next = L1;
            L1 = L1->next;
        } else {
            guard->next = L2;
            L2 = L2->next;
        }
        guard = guard->next;
    }

    guard->next = L1 == nullptr ? L2 : L1;
    return head->next;
}

ListNode* LinkTest::deleteNthFromEnd(ListNode* head, int n) {
        ListNode* guard = new ListNode(-1, head);
        ListNode* slow = guard;
        ListNode* fast = guard;

        while(n > 0 && fast != nullptr) {
            n--;
            fast = fast->next;
        }
        cout << fast->val <<endl;

        while(fast->next) {
            slow = slow->next;
            fast = fast->next;
        }
        cout << slow->val <<endl;
        slow->next = slow->next->next;

        ListNode* ans = guard->next;
        //attention here, memory leak;
        delete guard;
        return ans;
}

ListNode* LinkTest::deleteNthFromEndByStack(ListNode* head, int n) {
    ListNode* guard = new ListNode(-1, head);
    ListNode* cur   = guard;
    stack<ListNode*> checker;

    while(cur) {
        checker.push(cur);
        cur = cur->next;
    }

    while(n > 0) {
        n--;
        checker.pop();
    }

    ListNode* pre = checker.top();
    pre->next = pre->next->next;

    ListNode* ans = guard->next;
    delete guard;
    return ans;
}

ListNode* LinkTest::findMiddleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    //tips: fast should be jueded first to avoid nullptr bug.
    while(fast != nullptr && fast->next->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
