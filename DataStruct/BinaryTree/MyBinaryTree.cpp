/*
*
* https://blog.csdn.net/u010558281/article/details/74276577
*
*  g++ -o tree.out MyBinaryTree.cpp -std=c++11
*
* Memory Leak Test:
*     valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./tree.out
*/

/*
*
* https://blog.csdn.net/u010558281/article/details/74276577
*/
#include<iostream>
#include<stack>
#include<queue>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node():value(0){}
    Node(int _value):value(_value), left(nullptr), right(nullptr){}
};

class BinaryTree {
private:
    Node* m_rootNode;
public:
    BinaryTree(int val);
    ~BinaryTree(){};
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// @brief  insert node from m_rootNode.
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void insertNodeFromRoot(int value);
    void insertNode(Node* node, int value);
    void insertNodeNoIteration(int value);

    void preOrderFromRoot();
    void preOrder(Node* node);
    void preOrderNoIteration(Node* node);

    void inOrderFromRoot();
    void inOrder(Node* node);
    void inOrderNoIteration(Node* node);

    void postOrderFromRoot();
    void postOrder(Node* node);
    
    // Traverse by level.
    // leetcode 102.
    void levelOrderFromRoot();
    void levelOrder(Node* node);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// @brief  find target node by its value.
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Node* findTarget(int target);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// @brief  destroy the tree to avoid memory leak.
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void destroyTree();
    void destroyNode(Node* rootNode);

    int rightMin(Node* root);
    int leftMax(Node* root);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// @brief  delete target node - leetcode 450.
    ///
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void  deleteTargetNode(int target);
    Node* deleteNode(Node* root, int value);
};

BinaryTree::BinaryTree(int val)
{
    m_rootNode = new Node(val);
}

void BinaryTree::insertNodeFromRoot(int value)
{
    insertNode(m_rootNode, value);
}

void BinaryTree::insertNode(Node* node, int value)
{
    if(node->value >= value) {
        if(!node->left) {
            node->left = new Node(value);
            cout << "new a node " << node->left << " " << value << endl;
        }else{
            insertNode(node->left, value);
        }
    } else {
        if(!node->right) {
            node->right = new Node(value);
            cout << "new a node " << node->right << " " << value << endl;
        } else {
            insertNode(node->right, value);
        }
    }
}

void BinaryTree::insertNodeNoIteration(int value)
{
    if(m_rootNode == nullptr) {
        m_rootNode = new Node(value);
        return;
    }

    Node* p = m_rootNode;
    while(p != nullptr) {
        if(value <= p->value) {
            if(p->left == nullptr) {
                p->left = new Node(value);
                return;
            }
            p = p->left;
        } else {
            if(p->right == nullptr) {
                p->right = new Node(value);
                return;
            }
            p = p->right;
        }
    }
}

void BinaryTree::preOrderFromRoot()
{
    preOrder(m_rootNode);
}

void BinaryTree::preOrder(Node* node)
{
    if(node){
        cout << " " << node->value;
        preOrder(node->left);
        preOrder(node->right);
    }
}

void BinaryTree::preOrderNoIteration(Node* node)
{
    if(node == nullptr){
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

void BinaryTree::inOrderFromRoot()
{
    inOrder(m_rootNode);   
}

void BinaryTree::inOrder(Node* node)
{
    if(node){
        inOrder(node->left);
        cout << node->value;
        inOrder(node->right);
    }
}

void BinaryTree::inOrderNoIteration(Node* node)
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

void BinaryTree::levelOrderFromRoot()
{
    levelOrder(m_rootNode);
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

Node* BinaryTree::findTarget(int target)
{
    Node* pNode = m_rootNode;
    while(pNode != nullptr) {
        if(pNode->value > target) {
            pNode = pNode->left;
        } else if(pNode->value < target) {
            pNode = pNode->right;
        } else {
            return pNode;
        }
    }
    return nullptr;
}

//1.内存泄漏问题
void BinaryTree::destroyTree()
{
    destroyNode(m_rootNode);
}

void BinaryTree::destroyNode(Node* rootNode)
{
    if(rootNode) {
        cout << " destroyTree " << rootNode << " - " << rootNode->value << endl;
    }

    if(nullptr != rootNode){
        Node* left  = rootNode->left;
        Node* right = rootNode->right;

        delete rootNode;

        destroyNode(left);
        destroyNode(right);
    }
}

int BinaryTree::rightMin(Node* root)
{
    root = root->right;
    while (root->left != nullptr)
    {
        root = root->left;
    }
    return root->value;
}

int BinaryTree::leftMax(Node* root)
{
    root = root->left;
    while (root->right != nullptr)
    {
        root = root->right;
    }
    return root->value;
}

void BinaryTree::deleteTargetNode(int target)
{
    Node* tmp = deleteNode(m_rootNode, target);    
    cout << " tmp = " << tmp << endl;
}

Node* BinaryTree::deleteNode(Node* root, int value)
{
    if (root == nullptr) return nullptr;

    if (value > root->value)
    {
        root->right = deleteNode(root->right, value);
    } else if (value < root->value) {
        root->left = deleteNode(root->left, value);
    } else {
        // case 1: no children node
        if (root->left == nullptr && root->right == nullptr) {
            // tips: do not forget to release memory here.
            delete root;
            root = nullptr;
        // case 2: has right child node, replace value.
        } else if (root->right != nullptr) {
            root->value = rightMin(root);
            root->right = deleteNode(root->right, root->value);
        } else {
            root->value = leftMax(root);
            root->left  = deleteNode(root->left, root->value);
        }
    }
    return root;
}

int main()
{
    BinaryTree testTree(20);
    testTree.insertNodeFromRoot(10);
    testTree.insertNodeFromRoot(30);
    testTree.insertNodeFromRoot(8);
    testTree.insertNodeFromRoot(15);

    std::cout<<" levelOrder is:" << endl;
    testTree.levelOrderFromRoot();
    std::cout<<" preOrder is:" << endl;
    testTree.preOrderFromRoot();

    testTree.deleteTargetNode(20);
    cout << " after delete" << endl;
    testTree.levelOrderFromRoot();

    testTree.destroyTree();

    return 0;
}
