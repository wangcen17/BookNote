/**
*
*    Link:
*        https://github.com/wangzheng0822/algo/blob/master/c-cpp/08_stack/StackBasedOnLinkedList/StackBasedOnLinkedList.cpp
*/
#include<iostream>
using namespace std;

template<class T> class LinkListStack
{
public:
    LinkListStack();
    ~LinkListStack();

    void push(T data);
    T pop();  
    T peek();
    int getStackSize() const;

private:
    int m_count;
    struct LinkNode 
    {
        T data;
        LinkNode* pNext;
        LinkNode():pNext(NULL){}
        LinkNode(T input, LinkNode* next):data(input), pNext(next){}
        LinkNode(T input):data(input), pNext(NULL){}
    };
    LinkNode* m_pHead;
};

template<class T> LinkListStack<T>::LinkListStack()
{
    m_pHead = new LinkNode();
    m_count = 0;
    m_pHead->pNext = NULL;
}

template<class T> LinkListStack<T>::~LinkListStack()
{
    LinkNode* ptr, *temp;
    ptr = m_pHead;
    while (ptr->pNext != NULL)
    {
        temp = ptr->pNext;
        ptr  = temp->pNext;
        delete temp;
        temp = NULL;
    }
}

template<class T> void LinkListStack<T>::push(T data)
{
    LinkNode* newNode = new LinkNode(data);
    newNode->pNext = m_pHead->pNext;
    m_pHead->pNext = newNode;
    m_count++;
    cout << "push data : " << data << endl;
}

template<class T> T LinkListStack<T>::pop()
{
    if(m_count == 0 || m_pHead->pNext == NULL) {
        cout << "stack is empty ! " << endl;
        return -1;
    } else {
        LinkNode* ansNode = m_pHead->pNext;
        T ansData = ansNode->data;
        m_pHead->pNext = m_pHead->pNext->pNext;

        delete ansNode;
        ansNode = NULL;

        m_count--;
        return ansData;
    }
}

template<class T> T LinkListStack<T>::peek()
{
    if(m_count == 0 || m_pHead->pNext == NULL) {
        cout << "stack is empty ! " << endl;
        return -1;
    } else {
        LinkNode* ansNode = m_pHead->pNext;
        T ansData = ansNode->data;
        return ansData;
    }
}

template<class T> int LinkListStack<T>::getStackSize() const
{
    return m_count;
}

int main(int argc, char const *argv[])
{
    cout << " === StackBasedOnLinkedList test begin ===" << endl;
    LinkListStack <float> stack;
    cout << "size==="<<stack.getStackSize()<<endl;
    stack.push(10.1);
    stack.push(20.2);
    stack.push(30.);
    stack.push(40.4);
    stack.push(50.5);
    stack.push(60.6);
    cout << "size==="<<stack.getStackSize()<<endl;
    cout << "stack peek  " << stack.peek() << endl;
    cout << "stack pop  " << stack.pop() << endl;
    cout << "size==="<<stack.getStackSize()<<endl;
    cout << "stack pop  " << stack.pop() << endl;
    cout << "stack pop  " << stack.pop() << endl;
    cout << "stack pop  " << stack.pop() << endl;
    cout << "stack pop  " << stack.pop() << endl;
    cout << "stack pop  " << stack.pop() << endl;
    cout << "size==="<<stack.getStackSize()<<endl;
    cout << "stack pop  " << stack.pop() << endl;
    cout << "stack peek  " << stack.getStackSize() << endl;
    stack.push(110.1);
    stack.push(120.2);
    stack.push(130.3);
    stack.push(140.4);
    stack.push(150.5);
    stack.push(160.6);
    cout << "size==="<<stack.getStackSize()<<endl;
    cout << "stack peek  " << stack.getStackSize() << endl;
    cout << "stack pop  " << stack.pop() << endl;
    cout << "stack pop  " << stack.pop() << endl;
    cout << "stack pop  " << stack.pop() << endl;
    cout << "stack peek  " << stack.getStackSize() << endl;   //peek
    cout << "stack pop  " << stack.pop() << endl;
    cout << "stack pop  " << stack.pop() << endl;
    cout << "stack pop  " << stack.pop() << endl;
    cout << "size==="<<stack.getStackSize()<<endl;
    cout << "stack peek  " << stack.getStackSize() << endl;   //peek
    cout << "stack pop  " << stack.pop() << endl;    
    //system("pause");
    return 0;
}
