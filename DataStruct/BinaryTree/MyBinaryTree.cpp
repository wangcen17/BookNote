/*
*
* https://blog.csdn.net/u010558281/article/details/74276577
*
*  g++ -o tree.out MyBinaryTree.cpp -std=c++11
*
* Memory Leak Test:
*     valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./tree.out
*/
#include<iostream>
#include<stack>
#include<queue>
#include <memory>
using namespace std;


struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int _value):value(_value), left(), right(){}
};

class BinaryTree {
public:
    Node* m_rootNode;

    ~BinaryTree(){};
    // Binary Search Tree
    void insertNode(Node* node, int value);

    void preOrder(Node* node);
    void preOrder_NoIteraton(Node* node);

    void inOrder(Node* node);
    void inOrder_NoIteraton(Node* node);

    void postOrder(Node* node);
    
    // Traverse by level.
    // leetcode 102.
    void levelOrder(Node* node);

    void destroyTree(Node* rootNode);
};

void BinaryTree::insertNode(Node* node, int value)
{
    if(node->value >= value){
        if(!node->left) {
            node->left = new Node(value);
        }else{
            insertNode(node->left, value);
        }
    }else{
        if(!node->right){
            node->right = new Node(value);
        }else{
            insertNode(node->right, value);
        }
    }
}

void BinaryTree::preOrder(Node* node)
{
    if(node){
        cout << " " << node->value;
        preOrder(node->left);
        preOrder(node->right);
    }
}

void BinaryTree::preOrder_NoIteraton(Node* node)
{
    if(node == NULL){
        return;
    }

    stack<Node*> n_stack;
    n_stack.push(node);
    while(!n_stack.empty()){
        Node* temp = n_stack.top();
        cout << " " << temp->value << endl;
        n_stack.pop();

        if(temp->right){
            n_stack.push(temp->right);
        }

        if(temp->left){
            n_stack.push(temp->left);
        }
    }
}

void BinaryTree::inOrder(Node* node)
{
    if(node){
        inOrder(node->left);
        cout << node->value;
        inOrder(node->right);
    }
}

void inOrder_NoIteraton(Node* node)
{
    stack<Node*> n_stack;
    Node* temp = node;
    
}

void BinaryTree::postOrder(Node* node)
{
    if(node){
        postOrder(node->left);
        postOrder(node->right);
        cout << " " << node->value;
    }
}

void BinaryTree::levelOrder(Node* node)
{
    if(!node){
        return;
    }

    std:queue<Node*> q_node;
    q_node.push(node);

    while(!q_node.empty()){
        Node* temp = q_node.front();
        cout << " " << temp->value;
        q_node.pop();

        if(temp->left){
            q_node.push(temp->left);
        }

        if(temp->right){
            q_node.push(temp->right);
        }
    }
}

// 1. 值传递问题；
// 2. 内存泄露检测问题；
void BinaryTree::destroyTree(Node* rootNode)
{
    cout << " destroyTree = " << rootNode << endl;
     cout << " destroyTree = " << &rootNode << endl;
    if(NULL != rootNode){
        Node* left  = rootNode->left;
        Node* right = rootNode->right;

        delete rootNode;
        rootNode = NULL;

        destroyTree(left);
        destroyTree(right);
    }
}

int main()
{
    BinaryTree testTree;
    testTree.m_rootNode = new Node(20);
    testTree.insertNode(testTree.m_rootNode, 10);
    testTree.insertNode(testTree.m_rootNode, 8);
    // testTree.insertNode(testTree.m_rootNode, 11);
    // testTree.insertNode(testTree.m_rootNode, 30);
    // testTree.insertNode(testTree.m_rootNode, 31);
    // testTree.insertNode(testTree.m_rootNode, 29);

    cout << " value = " << testTree.m_rootNode->value << endl;
    cout << " addr = " << testTree.m_rootNode << endl;
    cout << " addr = " << &testTree.m_rootNode << endl;

    // std::cout<<" levelOrder is:";
    // testTree.levelOrder(testTree.m_rootNode);
    // std::cout<<" preOrder is:";
    // testTree.preOrder(testTree.m_rootNode);

    testTree.destroyTree(testTree.m_rootNode);
    bool flag = testTree.m_rootNode == NULL;
    cout << " falg = " << flag << endl;

    //m_rootNode can not be read because memory has been free.
    //cout << " addr = " << testTree.m_rootNode << endl;
    //cout << " value = "<< testTree.m_rootNode->value << endl;

    return 0;
}
