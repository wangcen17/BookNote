/**
 * 1）顺序栈的操作：入栈和出栈；
 * 2）采用模板的方法实现存储任意类型的数据
 * 3）采用数组的栈，支持动态扩容，每次扩容1.5 倍，初始栈的大小是 10 。
 * 
 * Author：caozx
 * time ；2018年10月11日
 * link: 
 *      https://github.com/wangzheng0822/algo/blob/master/c-cpp/08_stack/StackBasedOnArray/StackBasedOnArray.cpp
 */

#include<iostream>
using namespace std;


template <class T>
class ArrayStack
{
public:
    ArrayStack();
    ArrayStack(int count);
    ~ArrayStack();
    ArrayStack(const ArrayStack &obj);
    ArrayStack& operator = (const ArrayStack &obj);

    void push(T data);
    T pop();
    T top();
    int stackSize();
    int stackMaxSize();

private:
    int m_count;
    T* array;
    int m_flag;
};

template<class T> ArrayStack<T>::ArrayStack()
{
    this->m_count = 10;
    this->m_flag  = 0;
    this->array   = new T[this->m_count];

    if(!this->array) {
        cout << "array fail to malloc mem " << endl;
    }
}

template<class T> ArrayStack<T>::ArrayStack(int count)
{
    this->m_count = count;
    this->m_flag  = 0;
    this->array   = new T[this->m_count];

    if(!this->array) {
        cout << "array fail to malloc mem " << endl;
    }    
}

template<class T> ArrayStack<T>::~ArrayStack()
{
    this->m_count = 0;
    this->m_flag  = 0;
    if(this->array) {
        delete [] this->array;
        this->array = NULL;
    }
}

template<class T> void ArrayStack<T>::push(T data)
{
    if(this->m_flag == this->m_count) {
        cout << "this stack is full, need to enlarge 1.5x " << endl;
        this->m_count = int(1.5 * this->m_count);

        T* temp = new T[this->m_count];
        for(int i = 0; i < this->m_flag; i++) {
            temp[i] = this->array[i];
        }

        delete [] this->array;
        temp[this->m_flag] = data;
        this->m_flag++;
        this->array = temp;
    } else {
        this->array[this->m_flag] = data;
        this->m_flag++;
    }
}

template <class T> T ArrayStack<T>::pop() 
{
    this->m_flag--;
    T temp = this->array[this->m_flag];
    return temp;
}

template <class T> T ArrayStack<T>::top()
{
    return this->array[this->m_flag-1];
}

template <class T> int ArrayStack<T>::stackSize()
{
    return this->m_flag;
}

template <class T> int ArrayStack<T>::stackMaxSize()
{
    return this->m_count;
}

int main(int argc, char const *argv[])
{
    cout << " === test begin ===" << endl;
    ArrayStack <int> arrstack(12);
    arrstack.push(10);
    arrstack.push(20);
    arrstack.push(30);
    arrstack.push(40);
    arrstack.push(50);
    arrstack.push(60);
    arrstack.push(70);
    arrstack.push(80);
    arrstack.push(90);
    arrstack.push(100);
    arrstack.push(110);
    arrstack.push(120);
    arrstack.push(130);
    arrstack.push(140);
    arrstack.push(150);

    cout << "peek , not delete " << arrstack.top() << endl;
    cout << "pop , delete " << arrstack.pop()<<endl;
    
    arrstack.push(210);
    arrstack.push(220);

    cout << "peek , not delete " << arrstack.top() << endl;
    cout << "pop , delete " << arrstack.pop()<<endl;    
   
    //system("pause");
    return 0;
}
