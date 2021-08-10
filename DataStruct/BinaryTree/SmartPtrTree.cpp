/*
*
* https://blog.csdn.net/u010558281/article/details/74276577
*
* link:
*      https://codereview.stackexchange.com/questions/191211/binary-search-tree-data-structure-implementation-in-c11-using-smart-pointers
*/
#include<iostream>
#include<stack>
#include<queue>
#include <memory>
using namespace std;

template <typename key_t>
struct node {
    key_t key;
    weak_ptr<node>   parent;
    shared_ptr<node> left;
    shared_ptr<node> right;

    node(const key_t key) {
        this->key   = key;
        this->left  = nullptr;
        this->right = nullptr;
    }
};

template <typename key_t>
class Tree {
private:
    template <typename _key_t>
    struct node {
        _key_t key;
        weak_ptr<node>   parent;
        shared_ptr<node> left;
        shared_ptr<node> right;

        node(const key_t key) {
            this->key   = _key;
            this->left  = nullptr;
            this->right = nullptr;
        }
    };
    void preOrder(shared_ptr<node<key_t>> &x);
public:
    shared_ptr<node<key_t>> m_root;

    // ?? why this is quote.
    void preOrder();
    void inOrder(shared_ptr<node<key_t>> &x);
    void postOrder(shared_ptr<node<key_t>> &x);
    void insertNode(const key_t &key);
};

template <typename key_t> void Tree<key_t>::preOrder()
{
    preOrder(m_root);
}

template <typename key_t> void Tree<key_t>::preOrder(shared_ptr<node<key_t>> &x)
{
    if(x == nullptr) {
        return;
    }
    // TODO:
    //    how to pass int to here?
    cout << (int)x->key << " " << endl;
    preOrder(x->left);
    preOrder(x->right);
}

template <typename key_t> void Tree<key_t>::insertNode(const key_t &key)
{
    shared_ptr<node<key_t>> current = m_root;
    shared_ptr<node<key_t>> parent  = nullptr;
    while(current != nullptr) {
        parent = current;
        if(key > current->key) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    cout <<  "try to insert "  << (int)key << endl;
    current = make_shared<node<key_t>>(key);
    if(parent == nullptr) {
        m_root = current;
    } else if(current->key > parent->key) {
        parent->right = current;
    } else {
        parent->left = current;
    }
}

int main()
{
    Tree<int> testTree;
    cout <<  "test begin " << endl;
    testTree.insertNode(10);
    testTree.insertNode(5);
    testTree.insertNode(20);
    testTree.preOrder();
    return 0;
}

