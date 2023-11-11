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
    LinkedBinaryTree(){
        root = NULL;
        treeSize = 0;
    }
    LinkedBinaryTree(BinaryTreeNode<T>* p){
        root = p;
        treeSize = calculatetreeSize(root);
        
    }
    ~LinkedBinaryTree(){erase();}
    bool empty() const {
        return treeSize == 0;
    }
    int size() const {
        return treeSize;
    }
    void setFuncPointer(void (*pfunction)(BinaryTreeNode<T>*))
    {
        this->pfunction = pfunction;
    }
    void preOrder(void (*pfunction)(BinaryTreeNode<T>*));
    void inOrder(void (*pfunction)(BinaryTreeNode<T>*));
    void postOrder(void (*pfunction)(BinaryTreeNode<T>*));
    void levelOrder(void (*pfunction)(BinaryTreeNode<T>*));
    int calculatetreeSize(BinaryTreeNode<T>* p){
        if (p == NULL) return 0;
        int left = calculatetreeSize(p->leftChild);
        int right = calculatetreeSize(p->rightChild);
        return left + right + 1;
    }
    T* getRoot() const {
        if (treeSize == 0) return NULL;
        else return &(root->element);
    }
    void erase()
    {
        postOrder(dispose);
        root = NULL;
        treeSize = 0;
    }
    int height() {
        return height(root);
    }
    void preOrderOutput(){preOrder(output); cout << endl;}
    void inOrderOutput(){inOrder(output); cout << endl;}
    void postOrderOutput(){postOrder(output); cout << endl;}
    void levelOrderOutput(){levelOrder(output); cout << endl;}
    void makeTree(const T& element,LinkedBinaryTree<T>& left, LinkedBinaryTree<T>& right)
    {
        root = new BinaryTreeNode<T>(element,left.root, right.root);
        treeSize = left.treeSize + right.treeSize + 1;
        left.root = right.root = NULL;
        left.root = right.root = 0;
    }
protected:
    void preOrder(BinaryTreeNode<T>* p , void (*visit)(BinaryTreeNode<T>*));
    void inOrder(BinaryTreeNode<T>* p , void (*visit)(BinaryTreeNode<T>*));
    void postOrder(BinaryTreeNode<T>* p , void (*visit)(BinaryTreeNode<T>*));
    int height(BinaryTreeNode<T>* p);
    BinaryTreeNode<T> *root;
    int treeSize;
    void (*pfunction)(BinaryTreeNode<T>*);
    static void dispose(BinaryTreeNode<T>* t) {delete t;}
    static void output(BinaryTreeNode<T> *p){cout << p->element << ' ';}

};

template<class T>
void LinkedBinaryTree<T>::preOrder(void (*visit)(BinaryTreeNode<T>*))
{
    preOrder(root,visit);
}

template<class T>
void LinkedBinaryTree<T>::preOrder(BinaryTreeNode<T>* p , void (*visit)(BinaryTreeNode<T>*)){
    if(p != NULL) {
        visit(p);
        preOrder(p->leftChild,visit);
        preOrder(p->rightChild,visit);
    }
}

template<class T>
void LinkedBinaryTree<T>::inOrder(void (*visit)(BinaryTreeNode<T>*))
{
    inOrder(root,visit);
}


template<class T>
void LinkedBinaryTree<T>::inOrder(BinaryTreeNode<T>* p , void (*visit)(BinaryTreeNode<T>*)){
    if(p != NULL) {
        inOrder(p->leftChild,visit);
        visit(p);
        inOrder(p->rightChild,visit);
    }
}

template<class T>
void LinkedBinaryTree<T>::postOrder(void (*visit)(BinaryTreeNode<T>*))
{
    postOrder(root,visit);
}


template<class T>
void LinkedBinaryTree<T>::postOrder(BinaryTreeNode<T>* p , void (*visit)(BinaryTreeNode<T>*)){
    if(p != NULL) {
        postOrder(p->leftChild,visit);
        postOrder(p->rightChild,visit);
        visit(p);
    }
}


template<class T>
void LinkedBinaryTree<T>::levelOrder(void (*visit)(BinaryTreeNode<T>*))
{
    if (!root) return;
    ArrayQueue<BinaryTreeNode<T>*> queue;
    queue.push(root);
    while (!queue.empty())
    {
        BinaryTreeNode<T>*p = queue.front();
        queue.pop();
        visit(p);
        if (p->leftChild != NULL)
            queue.push(p->leftChild);
        if (p->rightChild != NULL)
            queue.push(p->rightChild);
    }
    

}
template<class T>
int LinkedBinaryTree<T>::height(BinaryTreeNode<T>* p){
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