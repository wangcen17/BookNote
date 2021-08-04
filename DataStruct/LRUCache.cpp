#include<iostream>
#include<map>
#include<vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
using namespace std;

struct DLinkNode {
    int key, value;
    DLinkNode* pPrev;
    DLinkNode* pNext;
    DLinkNode():key(0), value(0), pPrev(nullptr), pNext(nullptr) {};
    DLinkNode(int _key, int _value): key(_key), value(_value), pPrev(nullptr), pNext(nullptr){};
};

class LRUCache {
private:
    unordered_map<int, DLinkNode*> m_cache;
    DLinkNode* m_head;
    DLinkNode* m_tail;
    int m_size;
    int m_capacity;

public:
    LRUCache(int capacity) : m_capacity(capacity), m_size(0) {
        m_head = new DLinkNode();
        m_tail = new DLinkNode();
        m_haed->pNext = m_tail;
        m_tail->pPrev = m_head;
    }   

    ~LRUCache() {
        unprdered_map<int, DLinkNode*>::iterator it = m_cache.begin();
        while(it != m_cache.end()) {
            delete it->second;
            it->second = nullptr;
            m_cache.erase(it++);
        }

        delete m_head;
        delete m_tail;
        m_head = nullptr;
        m_tail = nullptr;
    }

    void addToHead(DLinkNode* node) {
        node->pPrev = m_head;
        node->pNext = m_head->pNext;
        m_head->pNext->pPrev = node;
        m_head->pNext = node;
    }

    void removeNode(DLinkNode* node) {
        node->pPrev->pNext = node->pNext;
        node->pNext->pPrev = node->pPrev;
    }

    void moveToHead(DLinkNode* node) {
        removeNode(node);
        addToHead(node);
    }

    DLinkNode* removeTail() {
        DLinkNode* node = m_tail->pPrev;
        removeNode(node);
        return node;
    }

    int get(int key) {
        if(!m_cache.count(key)) {
            return -1;
        }
        DLinkNode* node = m_cache[key];
        moveToHead(node);
        return node->value;
    }

    int put(int key, int value) {
        if(!m_cache.count(key)) {
            DLinkNode* node = new DLinkNode(key, value);
            m_cache[key] = node;
            addToHead(node);
            ++m_size;

            if(m_size > m_capacity) {
                DLinkNode* nodeToRemove = removeTail();
                m_cache.erase(nodeToRemove);
                delete nodeToRemove;
                --m_size;
            }
        } else {
            DLinkNode* node = m_cache[key];
            node->value = value;
            moveToHead(node);
        }
    }
};
