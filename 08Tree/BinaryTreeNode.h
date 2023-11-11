#ifndef __BinaryTreeNode__
#define __BinaryTreeNode__
#include <iostream>
template<class T>
struct BinaryTreeNode{
    T element;
    BinaryTreeNode<T> *leftChild;
    BinaryTreeNode<T> *rightChild;
    BinaryTreeNode(){
        leftChild = NULL;
        rightChild = NULL;
    }
    BinaryTreeNode(const T& theElement):element(theElement)
    {
        leftChild = NULL;
        rightChild = NULL;
    }

    BinaryTreeNode(const T& theElement, BinaryTreeNode* theLeftChild, BinaryTreeNode* theRightChild) : element(theElement)
    {
        leftChild = theLeftChild;
        rightChild = theRightChild;
    }
};

#endif