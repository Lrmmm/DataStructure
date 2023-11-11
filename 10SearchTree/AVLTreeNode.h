#ifndef __AVLTreeNode__
#define __AVLTreeNode__
#include<iostream>
using namespace std;
template<class K,class V>
struct AVLNode
{
    pair<const K,V> element;
    AVLNode<K,V> *leftChild;
    AVLNode<K,V> *rightChild;
    AVLNode<K,V> *parent;
    int bf;

    AVLNode(): leftChild(NULL),rightChild(NULL),parent(NULL),bf(0){}
    AVLNode(const pair<K,V>& theElement):element(theElement),
        leftChild(NULL),rightChild(NULL),parent(NULL),bf(0){}
    AVLNode(const pair<K,V>& theElement, AVLNode<K,V> *theLeftChild, 
            AVLNode<K,V> *theRightChild, AVLNode<K,V> *theParent):
            element(theElement),
            leftChild(theLeftChild),
            rightChild(theRightChild),
            parent(theParent),
            bf(0){}
    AVLNode(const pair<K,V>& theElement, AVLNode<K,V> *theLeftChild, 
            AVLNode<K,V> *theRightChild, AVLNode<K,V> *theParent,
            int theBf):
            element(theElement),
            leftChild(theLeftChild),
            rightChild(theRightChild),
            parent(theParent),
            bf(theBf){}
};
#endif