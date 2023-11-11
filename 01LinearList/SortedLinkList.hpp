#ifndef __SortedLinkList__
#define __SortedLinkList__

#include <iostream>
#include "../05Dictionary/Dictionary.h"

using namespace std;

template<class K, class V>
class SortedLinkList : public Dictionary<K,V>
{
public:
    struct PairNode
    {
        typedef pair<const K, V> PairType;
        PairType data;
        PairNode* next;
        PairNode(const PairType& thePair) : data(thePair) {}
        PairNode(const PairType& thePair, PairNode* theNext) :
            data(thePair), next(theNext){}
    };
    
    SortedLinkList(){head = NULL; nSize = 0;}
    ~SortedLinkList();

    bool empty() const {return nSize == 0;}
    int size() const {return nSize;}
    pair<const K, V>* find(const K&) const;
    void erase(const K&);
    void insert(const pair<const K, V>&);
    void output(ostream& out) const;

protected:
    PairNode* head;
    int nSize;
    
};

template<class K, class V>
SortedLinkList<K,V>::~SortedLinkList()
{
    while (head != NULL) 
    {
        PairNode* next = head->next;
        delete head;
        head = next;
    }
}

template<class K, class V>
pair<const K,V>* SortedLinkList<K,V>::find(const K& theKey) const
{
    PairNode* curr = head;

    while (curr != NULL && curr->data.first != theKey)
        curr = curr->next;

    if (curr != NULL && curr->data.first == theKey)   
        return &curr->data;
    return NULL; 
}

template<class K, class V>
void SortedLinkList<K,V>::insert(const pair<const K, V>& thePair)
{
    PairNode *p = head, *tp = NULL;

    while (p != NULL && p->data.first < thePair.first)
    {
        tp = p ;
        p = p->next;
    }

    if (p != NULL && p->data.first == thePair.first) {
        p->data.second = thePair.second;
        return;
    }

    PairNode *newNode = new PairNode(thePair, p);

    if (tp == NULL) head = newNode;
    else tp->next = newNode;

    nSize++;
    return;
    
}

template<class K, class V>
void SortedLinkList<K,V>::erase(const K& theKey)
{
    PairNode *p = head, *tp = NULL;

    while (p != NULL && p->data.first < theKey)
    {
        tp = p;
        p = p->next;
    }

    if (p != NULL && p->data.first == theKey)
    {
        if (tp == NULL) head = p->next;
        else tp->next = p->next;

        delete p;
        nSize--;
    }
    
}

template<class K, class V>
void SortedLinkList<K,V>::output(ostream& out) const
{
    for (PairNode* curr = head; curr != NULL; curr = curr->next)
    {
        out << curr->data.first << "," << curr->data.second <<" ";
    }
    
}

template<class K,class V>
ostream& operator<<(ostream& out, const SortedLinkList<K,V>& x)
{
    x.output(out);
    return out;
}

#endif