#ifndef __BinarySearchTree__
#define __BinarySearchTree__

#include "../08Tree/LinkedBinaryTree.hpp"
#include "../05Dictionary/Dictionary.h"
#include <iostream>
using namespace std;

template<class K, class V>
class BinarySearchTree : public Dictionary<K,V>, 
                        public LinkedBinaryTree<pair<const K,V>>
{
public:
    bool empty() const {return this->treeSize == 0;}
    int size() const{return this->treeSize;}
    pair<const K,V>* find(const K& theKey) const;
    void insert(const pair<const K,V>& thePair);
    void erase(const K& theKey);
    void ascend() {LinkedBinaryTree<pair<const K,V>>::inOrderOutput();}
};

template<class K, class V>
pair<const K,V>* BinarySearchTree<K,V>::find(const K& theKey) const
{
    BinaryTreeNode<pair<const K,V>> *p = this->root;
    while (p != NULL)
    {
        if (theKey == p->element.first)
            return &p->element;
        else if (theKey < p->element.first)
            p = p->leftChild;
        else 
            p = p->rightChild;

    }
    return NULL;
}

template<class K, class V>
void BinarySearchTree<K,V>::insert(const pair<const K,V>& thePair)
{
    if (this->root == NULL){
        this->root = new BinaryTreeNode<pair<const K,V>>(thePair);
        this->treeSize++;
        return;
    }

    BinaryTreeNode<pair<const K, V>> *p = this->root;
    BinaryTreeNode<pair<const K, V>> *pp = NULL;

    while (p != NULL)
    {
        pp = p;
        if (thePair.first == p->element.first){
            p->element.second = thePair.second;
            return ;
        }
        else if(thePair.first < p->element.first)
            p = p->leftChild;
        else
            p = p->rightChild;
    }
    
    BinaryTreeNode<pair<const K, V>> *newNode = 
        new BinaryTreeNode<pair<const K,V>>(thePair);
    
    if (thePair.first < pp->element.first)
        pp->leftChild = newNode;
    else
        pp->rightChild = newNode;

    (this->treeSize)++;
}

template<class K, class V>
void BinarySearchTree<K,V>::erase(const K& theKey)
{
    BinaryTreeNode<pair<const K,V>> *pDel = this->root;
    BinaryTreeNode<pair<const K,V>> *ppDel = NULL;

    // 查找要删除的结点pDel，和其父结点ppDel
    while (pDel != NULL && pDel->element.first != theKey)
    {
        ppDel = pDel;
        if (theKey < pDel->element.first)
            pDel = pDel->leftChild;
        else
            pDel = pDel->rightChild;
    }
    if (pDel == NULL)
        return ;
    this->treeSize--;

    // case1: 左子树为空，右子树顶上
    if(pDel->leftChild == NULL){
        if (ppDel == NULL)
            this->root = pDel->rightChild;
        else if(ppDel->leftChild == pDel)
            ppDel->leftChild = pDel->rightChild;
        else
            ppDel->rightChild = pDel->rightChild;
        delete pDel;
        return;
    }
    // case2: 右子树为空，左子树顶上
    if(pDel->rightChild == NULL){
        if (ppDel == NULL)
            this->root = pDel->leftChild;
        else if(ppDel->leftChild == pDel)
            ppDel->leftChild = pDel->leftChild;
        else
            ppDel->rightChild = pDel->leftChild;
        delete pDel;
        return ;
    }

    // case3: 左右子树都不空,第一，选择pDel的左子树最大结点pLeftMax代替
    BinaryTreeNode<pair<const K,V>> *pLeftMax = pDel->leftChild;
    BinaryTreeNode<pair<const K,V>> *ppLeftMax = pDel;
    while (pLeftMax->rightChild != NULL)
    {
        ppLeftMax = pLeftMax;
        pLeftMax = pLeftMax->rightChild;
    }

    if(pDel == ppLeftMax)
        ppLeftMax->leftChild = pLeftMax->leftChild;
    else
        ppLeftMax->rightChild = pLeftMax->leftChild;
    
    pLeftMax->leftChild = pDel->leftChild;
    pLeftMax->rightChild = pDel->rightChild;

    if(ppDel == NULL)
        this->root = pLeftMax;
    else if(ppDel->leftChild == pDel)
        ppDel->leftChild = pLeftMax;
    else
        ppDel->rightChild = pLeftMax;
    
    delete pDel;
}

template<class K, class V>
ostream& operator<<(ostream& out, const pair<K,V> &x)
{
    out << x.first << " " <<x.second;
    return out;
}

#endif