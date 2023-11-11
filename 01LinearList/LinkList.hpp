#ifndef __LinkList__
#define __LinkList__
#include "LinearList.h"
#include "../exception/myException.h"
template<class T>
class LinkList : public LinearList<T>{
public:
    struct Node {
        T data;
        Node *next;
        Node(const T& data) {this->data = data;}
        Node(const T& data, Node* next) {this->data = data; this->next = next;}
    };

    LinkList(int initCapacity = 1);
    LinkList(const LinkList<T>&);
    ~LinkList();

    // Override
    bool empty() const override {return nSize==0; }
    int size() const override {return nSize;}
    T& get(int nIndex) const override;
    int indexOf(const T& elem) const override;
    void erase(int nIndex) override;
    void insert(int nIndex, const T& elem);
    void output(ostream& out) const override;
    void push_back(const T& elem) {
        insert(nSize, elem);
    }
    void pop() {
        erase(nSize - 1);
    }

protected:
    void checkIndex(int nIndex) const;
    Node* head;
    int nSize;
};

template<class T>
void LinkList<T>::checkIndex(int nIndex) const
{
    if (nIndex < 0 || nIndex >= nSize) 
        throw illegalIndex("illegalIndex");
}

template<class T>
LinkList<T>::LinkList(int initCapacity)
{
    if (initCapacity < 1) {
        throw illegalParameterValue("illegalParameterValue");
    }
    head = NULL;
    nSize = 0;
}

template<class T>
LinkList<T>::LinkList(const LinkList<T>& sourceList ){
    nSize = sourceList.nSize;

    if (nSize == 0)
    {   
        head = NULL;
        return;
    }

    Node* pSource = sourceList.head;
    head = new Node(pSource->data);
    pSource = pSource->next;
    Node* pTarget = head;

    while(pSource != NULL) {
        pTarget->next = new Node(pSource->data);
        pTarget = pTarget->next;
        pSource = pSource->next;
    }

    pTarget->next = NULL;
}

template<class T>
LinkList<T>::~LinkList()
{
    while (head != NULL) {
        Node* pNext = head->next;
        delete head;
        head = pNext;
    }
}

template<class T>
T& LinkList<T>::get(int nIndex) const
{
    checkIndex(nIndex);

    Node* pCurNode = head;
    for (int i = 0; i < nIndex; i++)
    {
        pCurNode = pCurNode->next;
    }
    return pCurNode->data;
}

template<class T>
int LinkList<T>::indexOf(const T& elem) const
{
    Node* pCur = head;
    int nIndex = 0;
    while(pCur != NULL && pCur->data != elem){
        pCur = pCur->next;
        nIndex++;
    }

    if (pCur == NULL) return -1;
    else 
        return nIndex;
}

template<class T>
void LinkList<T>::erase(int nIndex)
{
    checkIndex(nIndex);

    Node* pDeleteNode;

    if (nIndex == 0) {
        pDeleteNode = head;
        head = head->next;
    }
    else {
        Node* pPre = head;
        for (int i = 0; i < nIndex - 1; i++)
            pPre = pPre->next;
        
        pDeleteNode = pPre->next;
        pPre->next = pPre->next->next;
    }
    nSize--;
    delete pDeleteNode;
}

template<class T>
void LinkList<T>::insert(int nIndex, const T& elem)
{
    if (nIndex < 0 || nIndex > nSize)
        throw illegalIndex("illegalIndex");
    
    if (nIndex == 0)
        head = new Node(elem, head);
    else {
        Node* pPre = head;
        for (int i = 0; i < nIndex - 1; i++)
            pPre = pPre->next;
        pPre->next = new Node(elem, pPre->next);
    }
    nSize++;
}

template<class T>
void LinkList<T>::output(ostream& out) const
{
    for (Node* p = head; p != NULL; p = p->next)
    {
        out << p->data << " ";
    }
    
}

template<class T>
ostream& operator<<(ostream& out, const LinkList<T>& x)
{
    x.output(out);
    return out;
}



#endif