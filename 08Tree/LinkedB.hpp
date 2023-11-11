#ifndef __LinkedBinaryTree__
#define __LinkedBinaryTree__
#include "BinaryTree.hpp"
#include "BinaryTreeNode.h"
#include "../exception/myException.h"
#include "../04Queue/ArrayQueue.hpp"
#include <iostream>
using namespace std;

template<class T>
class LinkedBinaryTree : public  BinaryTree<BinaryTreeNode<T>> {
public:
    LinkedBinaryTree() {m_pRoot = NULL; m_size = 0;}
    LinkedBinaryTree(BinaryTreeNode<T>* root) {
        m_pRoot = root;

    }
    ~LinkedBinaryTree(){erase();}
    bool empty() const {return m_size == 0;}
    int size() const {return m_size;}
    T* getRoot() const {
        if (m_size == 0) return NULL;
        else return &(m_pRoot->element);
    }
    void makeTree(const T& clElement,LinkedBinaryTree<T>&, LinkedBinaryTree<T>&);
    LinkedBinaryTree<T>& removeLeftSubTree();
    LinkedBinaryTree<T>& removeRightSubTree();
    void preOrder(void(*pfunVisit)(BinaryTreeNode<T>*))
    {
        m_pfunVisit = pfunVisit;
        preOrder(m_pRoot);
    }
    void inOrder(void(*pfunVisit)(BinaryTreeNode<T>*))
    {
        m_pfunVisit = pfunVisit;
        inOrder(m_pRoot);
    }
    void postOrder(void(*pfunVisit)(BinaryTreeNode<T>*))
    {
        m_pfunVisit = pfunVisit;
        postOrder(m_pRoot);
    }
    void levelOrder(void(*) (BinaryTreeNode<T>*));
    void preOrderOutput(){preOrder(output); cout << endl;}
    void inOrederOutput(){inOrder(output); cout << endl;}
    void postOrederOutput(){postOrder(output); cout << endl;}
    void levelOrederOutput(){levelOrder(output); cout << endl;}
    void erase()
    {
        postOrder(dispose);
        m_pRoot = NULL;
        m_size = 0;
    }
    int height() const {return height(m_pRoot);}
    int computeSize(BinaryTreeNode<T>*pNode) const {
        if (!pNode) return 0;
        int left = computeSize(pNode->leftChild);
        int right = computeSize(pNode->rightChild);
        return left + right + 1;
    }
public:
    BinaryTreeNode<T> *m_pRoot;
    int m_size;
    static void (*m_pfunVisit)(BinaryTreeNode<T>*);
    static void preOrder(BinaryTreeNode<T>* t);
    static void inOrder(BinaryTreeNode<T>* t);
    static void postOrder(BinaryTreeNode<T>* t);
    static void dispose(BinaryTreeNode<T>* t){delete t;}
    static int m_count;
    static void countNodes(BinaryTreeNode<T> *pclNode)
    {
        m_pfunVisit = addToCount;
        m_count = 0;
        preOrder(pclNode);
    }
    static void output(BinaryTreeNode<T> *pclNode){
        cout << pclNode->element << ' ';
    }
    static void addToCount(BinaryTreeNode<T> *pclNode){
        m_count++;
    }
    static int height(BinaryTreeNode<T> *pclNode);
};


template<class T>
void LinkedBinaryTree<T>::preOrder(BinaryTreeNode<T>* pclNode)
{
    if (pclNode != NULL){
        LinkedBinaryTree<T>::m_pfunVisit(pclNode);
        preOrder(pclNode->leftChild);
        preOrder(pclNode->rightChild);
    }
}

template<class T>
void LinkedBinaryTree<T>::inOrder(BinaryTreeNode<T>* pclNode)
{
    if (pclNode != NULL){
        inOrder(pclNode->leftChild);
        LinkedBinaryTree<T>::m_pfunVisit(pclNode);
        inOrder(pclNode->rightChild);
        
    }
}

template<class T>
void LinkedBinaryTree<T>::postOrder(BinaryTreeNode<T>* pclNode)
{
    if (pclNode != NULL){
        postOrder(pclNode->leftChild);
        postOrder(pclNode->rightChild);
        LinkedBinaryTree<T>::m_pfunVisit(pclNode);
    }
}

template<class T>
void LinkedBinaryTree<T>::levelOrder(void (*pVisit)(BinaryTreeNode<T>*))
{
    ArrayQueue<BinaryTreeNode<T>*> queue;
    queue.push(m_pRoot);
    while (!queue.empty())
    {
        BinaryTreeNode<T>* p = queue.front();
        queue.pop();
        pVisit(p);
        if (p->leftChild != NULL)
            queue.push(p->leftChild);
        if (p->rightChild != NULL)
            queue.push(p->rightChild);

    }
}

template<class T>
void LinkedBinaryTree<T>::makeTree(const T& element,LinkedBinaryTree<T>& left, LinkedBinaryTree<T>& right)
{
    m_pRoot = new BinaryTreeNode<T>(element,left.m_pRoot, right.m_pRoot);
    m_size = left.m_size + right.m_size + 1;
    left.m_pRoot = right.m_pRoot = NULL;
    left.m_size = right.m_size = 0;
}

template<class T>
LinkedBinaryTree<T>& LinkedBinaryTree<T>::removeLeftSubTree()
{
    if (m_size == 0)
        throw EmptyTree("emptyTree");
    
    LinkedBinaryTree<T> leftSubTree;
    leftSubTree.m_pRoot = m_pRoot->leftChild;
    m_count = 0;
    countNodes(leftSubTree.m_pRoot);
    leftSubTree.m_size = m_count;
    m_pRoot->leftChild = NULL;
    m_size -= leftSubTree.m_size;
    
    return leftSubTree;
}

template<class T>
LinkedBinaryTree<T>& LinkedBinaryTree<T>::removeRightSubTree()
{
    if (m_size == 0)
        throw EmptyTree("emptyTree");
    
    LinkedBinaryTree<T> rightSubTree;
    rightSubTree.m_pRoot = m_pRoot->rightChild;
    m_count = 0;
    countNodes(rightSubTree.m_pRoot);
    rightSubTree.m_size = m_count;
    m_pRoot->rightChild = NULL;
    m_size -= rightSubTree.m_size;
    
    return rightSubTree;
}

template<class T>
int LinkedBinaryTree<T>::height(BinaryTreeNode<T> *p)
{
    if (p == NULL)
        return 0;
    int hl = height(p->leftChild);
    int hr = height(p->rightChild);
    if(hl > hr)
        return ++hl;
    else 
        return ++hr;
}

#endif