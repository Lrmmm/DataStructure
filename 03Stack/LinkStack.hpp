#ifndef __LinkStack__
#define __LinkStack__
#include <iostream>
#include "Stack.h"
#include "../exception/myException.h"
using namespace std;
template<class T>
class LinkStack : public Stack<T>
{
public:
    struct Node {
        T data;
        Node *next;
        Node(const T& data) {this->data = data;}
        Node(const T& data, Node* next) {this->data = data; this->next = next;}
    };
    LinkStack(int initCapacity = 1) {
        pTop = NULL;
        nSize = 0;
    }
    ~LinkStack();
    bool empty() const {
        return nSize == 0;
    }
    int size() const {
        return nSize;
    }
    T& top() {
        if (nSize == 0)
            throw StackEmpty("StackEmpty");
        return pTop->data;
    }
    void pop();
    void push(const T& elem) {
        pTop = new Node(elem, pTop);
        nSize++;
    }
    void output(ostream& out) const {
        
        for (Node* p = pTop; p != NULL; p = p->next)
        {
            out << p->data << " ";
        }
        cout << endl;
    }
    friend ostream& operator<<(ostream& out, const LinkStack<T>& x)
    {
        x.output(out);
        return out;
    }
private:
    Node* pTop;
    int nSize;

};

template<class T>
LinkStack<T>::~LinkStack()
{
    while(pTop != NULL) {
        Node* temp = pTop->next;
        delete pTop;
        pTop = temp;
    }
}

template<class T>
void LinkStack<T>::pop()
{
    if (nSize == 0)
        throw StackEmpty("StackEmpty");

    Node* temp = pTop->next;
    delete pTop;
    pTop = temp;
    nSize--;
}

#endif