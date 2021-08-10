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

class Tree {
private:
    template <typename key_t>
    //Tips:put node as private;
    // 1.the tree code it can be referenced as node rather than node<key_t>
    // 2. the node is an implementation detail that need not be exposed to the user of the tree. 
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
public:
    shared_ptr<node<key_t>> m_root;
    void preOrder(shared_ptr<node<key_t>> &x);
    // ?? why this is quote.
    void preOrder();
    void inOrder(shared_ptr<node<key_t>> &x);
    void postOrder(shared_ptr<node<key_t>> &x);
    void insertNode(const key_t &key);
};

//template <typename key_t> void Tree<key_t>::preOrder()
void Tree::preOrder()
{
    preOrder(m_root);
}

//template <typename key_t> void Tree<key_t>::preOrder(shared_ptr<node<key_t>> &x)
void Tree::preOrder(shared_ptr<node<key_t>> &x)
{
    if(x == nullptr) {
        return;
    }
    // TODO:
    //    how to pass int to here?
    cout << x->key << " " << endl;
    preOrder(x->left);
    preOrder(x->right);
}

//template <typename key_t> void Tree<key_t>::insertNode(const key_t &key)
void Tree::insertNode(const key_t &key)
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
    Tree testTree;
    cout <<  "test begin " << endl;
    testTree.insertNode(10);
    testTree.insertNode(5);
    testTree.insertNode(20);
    testTree.preOrder();
    return 0;
}
