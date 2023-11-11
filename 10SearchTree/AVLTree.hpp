#ifndef __AVLTree__
#define __AVLTree__

#include "../08Tree/LinkedBinaryTree.hpp"
#include "../05Dictionary/Dictionary.h"
#include <iostream>
#include "./AVLTreeNode.h"
using namespace std;
template<class K, class V>
class AVLTree
{
public:
    // typedef AVLNode<K,V> Node;
    AVLTree(){root = NULL; treeSize = 0;}
    ~AVLTree(){erase();}
    bool empty() const {return treeSize == 0;}
    int size() const {return treeSize;}
    void preOrder(void (*pfunction)(AVLNode<K,V>*));
    void inOrder(void (*pfunction)(AVLNode<K,V>*));
    void postOrder(void (*pfunction)(AVLNode<K,V>*));
    void levelOrder(void (*pfunction)(AVLNode<K,V>*));
    void insert(const pair<const K,V>& thePair);
    void preOrderOutput(){preOrder(output);cout << endl;}
    void inOrderOutput(){inOrder(output);cout << endl;}
    void postOrderOutput(){postOrder(output);cout << endl;}
    void levelOrderOutput(){levelOrder(output);cout << endl;}
    void LeftLeft(AVLNode<K,V>* parent);
    void LeftRight(AVLNode<K,V>* parent);
    void RightRight(AVLNode<K,V>* parent);
    void RightLeft(AVLNode<K,V>* parent);
    void erase(){
        postOrder(dispose);
        root = NULL;
        treeSize = 0;
    }
    void remove(const K& theKey);
private:
    void preOrder(AVLNode<K,V> *p , void (*visit)(AVLNode<K,V>*));
    void inOrder(AVLNode<K,V>* p , void (*visit)(AVLNode<K,V>*));
    void postOrder(AVLNode<K,V>* p , void (*visit)(AVLNode<K,V>*));
    static void output(AVLNode<K,V> *p){cout<<p->element.first <<":"<<p->element.second<<' ';};
    static void dispose(AVLNode<K,V> *p){delete p;}
    AVLNode<K,V> *root;
    int treeSize;
};

template<class K, class V>
void AVLTree<K,V>::insert(const pair<const K,V>& thePair)
{
    if (root == NULL){
        root = new AVLNode<K,V>(thePair);
        treeSize++;
        return;
    }

    AVLNode<K,V>* curr = root;
    AVLNode<K,V>* parent = NULL;

    while(curr != NULL)
    {
        parent = curr;
        if (thePair.first == curr->element.first){
            curr->element.second = thePair.second;
            return;
        }
        else if(thePair.first < curr->element.first)
            curr = curr->leftChild;
        else 
            curr = curr->rightChild;
    }

    curr = new AVLNode<K,V>(thePair);

    if (thePair.first < parent->element.first)
        parent->leftChild = curr;
    else 
        parent->rightChild = curr;
    curr->parent = parent;
    treeSize++;

    // 自底向上更新平衡因子
    // 平衡因子:左子树 - 右子树
    while (parent)
    {
        if (curr == parent->leftChild)
            parent->bf++;
        else
            parent->bf--;
        
        // 父结点的平衡因子 -1->0 , 1->0，说明以父节点为根节点的子树高度没有变化
        if (parent->bf == 0) break;  // 说明pp结点之前有一个孩子,加入另一个孩子后平衡了,不改变树高
        // 父结点的平衡因子 0->-1 , 0->1，说明以父节点为根节点的子树高度增加，需要向上传递
        else if(parent->bf == -1 || parent->bf == 1) // 说明插入之前pp没有孩子，此状态时，插入的结点改变了树高，要向上传递
        {
            curr = parent;
            parent = parent->parent;
        }
        else{
            // 父节点平衡因子1->2,左子树比右子树高2，失衡
            if(parent->bf == 2) {
                if (curr->bf == 1)
                    LeftLeft(parent);
                else
                    LeftRight(parent);
            }
            // 右子树比左子树高2，失衡
            else {
                if (curr->bf == -1)
                    RightRight(parent);
                else 
                    RightLeft(parent);
            }
            break;
        }
    }
}

template<class K, class V>
void AVLTree<K,V>::LeftLeft(AVLNode<K,V>* parent)
{
    AVLNode<K,V>* childL = parent->leftChild;
    AVLNode<K,V>* childLchildR =  childL->rightChild;
    AVLNode<K,V>* pparent = parent->parent;

    if(pparent == NULL)
        root = childL;
    else if(pparent->leftChild == parent)
        pparent->leftChild = childL;
    else if(pparent->rightChild == parent)
        pparent->rightChild = childL;
    childL->parent = pparent;

    parent->leftChild = childLchildR;
    if (childLchildR)
        childLchildR->parent = parent;

    childL->rightChild = parent;
    parent->parent = childL;

    parent->bf = 0;
    childL->bf = 0;
}

template<class K, class V>
void AVLTree<K,V>::LeftRight(AVLNode<K,V>* parent)
{
    AVLNode<K,V>* childL = parent->leftChild;
    AVLNode<K,V>* childLchildR = childL->rightChild;
    int BF = childLchildR->bf;
    RightRight(childL);
    LeftLeft(parent);
    if(BF == 1) // 左边高
        parent->bf = -1;
    else
        childL->bf = 1;
}

template<class K, class V>
void AVLTree<K,V>::RightRight(AVLNode<K,V>* parent)
{
    AVLNode<K,V>* childR = parent->rightChild;
    AVLNode<K,V>* childRchildL =  childR->leftChild;
    AVLNode<K,V>* pparent = parent->parent;

    if(pparent == NULL)
        root = childR;
    else if(pparent->leftChild == parent)
        pparent->leftChild = childR;
    else if(pparent->rightChild == parent)
        pparent->rightChild = childR;
    childR->parent = pparent;

    parent->rightChild = childRchildL;
    if(childRchildL)
        childRchildL->parent = parent;

    childR->leftChild = parent;
    parent->parent = childR;

    parent->bf = 0;
    childR->bf = 0;
}
template<class K, class V>
void AVLTree<K,V>::RightLeft(AVLNode<K,V>* parent)
{
    AVLNode<K,V>* childR = parent->rightChild;
    AVLNode<K,V>* childRchildL = childR->leftChild;
    int BF = childRchildL->bf;
    LeftLeft(childR);
    RightRight(parent);
    if(BF == 1) // 左边高
        childR->bf = -1;
    else
        parent->bf = 1;
}



template<class K, class V>
void AVLTree<K,V>::preOrder(void (*visit)(AVLNode<K,V>*))
{
    preOrder(root,visit);
}

template<class K, class V>
void AVLTree<K,V>::preOrder(AVLNode<K,V>* p , void (*visit)(AVLNode<K,V>*)){
    if(p != NULL) {
        visit(p);
        preOrder(p->leftChild,visit);
        preOrder(p->rightChild,visit);
    }
}

template<class K, class V>
void AVLTree<K,V>::inOrder(void (*visit)(AVLNode<K,V>*))
{
    inOrder(root,visit);
}


template<class K, class V>
void AVLTree<K,V>::inOrder(AVLNode<K,V>* p , void (*visit)(AVLNode<K,V>*)){
    if(p != NULL) {
        inOrder(p->leftChild,visit);
        visit(p);
        inOrder(p->rightChild,visit);
    }
}

template<class K, class V>
void AVLTree<K,V>::postOrder(void (*visit)(AVLNode<K,V>*))
{
    postOrder(root,visit);
}


template<class K, class V>
void AVLTree<K,V>::postOrder(AVLNode<K,V>* p , void (*visit)(AVLNode<K,V>*)){
    if(p != NULL) {
        postOrder(p->leftChild,visit);
        postOrder(p->rightChild,visit);
        visit(p);
    }
}


template<class K, class V>
void AVLTree<K,V>::levelOrder(void (*visit)(AVLNode<K,V>*))
{
    if (!root) return;
    ArrayQueue<AVLNode<K,V>*> queue;
    queue.push(root);
    while (!queue.empty())
    {
        AVLNode<K,V>*p = queue.front();
        queue.pop();
        visit(p);
        if (p->leftChild != NULL)
            queue.push(p->leftChild);
        if (p->rightChild != NULL)
            queue.push(p->rightChild);
    }
}

template<class K, class V>
void AVLTree<K,V>::remove(const K& theKey)
{
    AVLNode<K,V> *pDel = this->root;
    AVLNode<K,V> *ppDel = NULL;

    // 查找要删除的结点pDel，其父结点ppDel
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

    if (pDel->leftChild != NULL && pDel->rightChild != NULL)
    {
        AVLNode<K,V> *pLeftMax = pDel->leftChild;
        AVLNode<K,V> *ppLeftMax = pDel;
        while (pLeftMax->rightChild != NULL)
        {
            ppLeftMax = pLeftMax;
            pLeftMax = pLeftMax->rightChild;
        }

        AVLNode<K,V> * newNode = new AVLNode<K,V>(pLeftMax->element,pDel->leftChild, 
                                    pDel->rightChild,ppDel,pDel->bf);
        pDel->leftChild->parent = newNode;
        pDel->rightChild->parent = newNode;

        if(ppDel == NULL)
            root = newNode;
        else if(pDel == ppDel->leftChild)
            ppDel->leftChild = newNode;
        else
            ppDel->rightChild = newNode;

        if(ppLeftMax == pDel) 
            ppDel = newNode;
        else 
            ppDel = ppLeftMax;

        delete pDel;
        pDel = pLeftMax;
    }

    AVLNode<K,V> *pDelChild;
    if (pDel->leftChild != NULL)
        pDelChild = pDel->leftChild;
    else
        pDelChild = pDel->rightChild;

    if(pDel == root) {  // 删除根节点，平衡因子不变
        root = pDelChild;
        if (pDelChild)
            pDelChild->parent = NULL;
        delete pDel;
        return;
    }
    // 删除非根结点，结点pDel肯定有父结点。其父节点ppDel指向其孩子结点pDelChild
    // 更新父结点的平衡因子
    else if(pDel == ppDel->leftChild) 
    {
        ppDel->leftChild = pDelChild;
        if(pDelChild) pDelChild->parent = ppDel;
        ppDel->bf--;
    }
    else {
        ppDel->rightChild = pDelChild;
        if(pDelChild) pDelChild->parent = ppDel;
        ppDel->bf++;
    }

    AVLNode<K,V> *pCur = ppDel;
    while (pCur)
    {
        // 父结点的平衡因子 0->1, 0->-1说明没有减少高度，break
        if (pCur->bf == 1 || pCur->bf == -1) break;
        // 父结点的平衡因子 1->0, -1->0,说明其高度减少，要往上传递，break
        else if(pCur->bf == 0){
            if(pCur->parent && pCur == pCur->parent->leftChild) pCur->parent->bf--;
            else if(pCur->parent && pCur == pCur->parent->rightChild) pCur->parent->bf++;
            pCur = pCur->parent;
        }
        // 失衡,R型，删除结点在失衡结点的右子树
        else if(pCur->bf == 2){
            // 2-0:R0型失衡
            if(pCur->leftChild->bf == 0){
                LeftLeft(pCur);
                pCur->bf = 1;
                pCur->parent->bf = -1;
                break;
            }
            // 2-1:R1型失衡
            else if(pCur->leftChild->bf == 1){
                LeftLeft(pCur);
                pCur->bf = 0;
                pCur->parent->bf = 0;
                pCur = pCur->parent;
            }
            // 2--1:R-1型失衡
            else if(pCur->leftChild->bf == -1){
                AVLNode<K,V> *parent = pCur;
                AVLNode<K,V> *childL = parent->leftChild;
                AVLNode<K,V> *childLchildR = childL->rightChild;
                int BF = childLchildR->bf;
                LeftRight(pCur);
                childLchildR->bf = 0;
                parent->bf = BF == 1 ? -1 : 0;
                childL->bf = BF == -1 ? 1 : 0;
                pCur = childLchildR;
            }
        }
        // 失衡,L型，删除结点在失衡结点的左子树
        else if(pCur->bf == -2){
            // 2-0:L0型失衡
            if(pCur->rightChild->bf == 0){
                RightRight(pCur);
                pCur->bf = -1;
                pCur->parent->bf = 1;
                break;
            }
            // 2--1:L-1型失衡
            else if(pCur->rightChild->bf == -1)
            {
                RightRight(pCur);
                pCur->bf = 0;
                pCur->parent->bf = 0;
                pCur = pCur->parent;
            }
            else if(pCur->rightChild->bf == 1)
            {
                AVLNode<K,V> *parent = pCur;
                AVLNode<K,V> *childR = parent->rightChild;
                AVLNode<K,V> *childRchildL = childR->leftChild;
                int BF = childRchildL->bf;
                RightLeft(pCur);
                childRchildL->bf = 0;
                parent->bf = BF == -1 ? 1 : 0;
                childR->bf = BF == 1 ? -1 : 0;
                pCur = childRchildL;
            }
        }
    }
    delete pDel;
}
#endif