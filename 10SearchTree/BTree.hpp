#pragma once
#include <iostream>
#include <queue>
using namespace std;

template<class K,int T>
struct BTreeNode
{
    BTreeNode()
    {
        for (int i = 0; i < 2*T; i++)
        {
            _keys[i] = K();
            _children[i] = NULL;
        }
        _parent = NULL;
        _children[2*T] = NULL;
        _size = 0;
        _isLeaf = true;
    }
    bool isLeaf(){
        for (int i = 0; i <= _size; i++)
            if (_children[i])
                return false;
        return true;
    }

    void printNode(){
        for (int i =1; i < 2*T; i++)
            cout<<_keys[i]<<" ";
        cout <<";";
    }
    K _keys[2*T]; // 最多2T-1个结点，这里第一个结点我们不用
    BTreeNode<K,T> *_children[2*T + 1];
    BTreeNode<K,T> *_parent;
    int _size;
    bool _isLeaf;
};

template<class K, int T>
class BTree{
    typedef BTreeNode<K,T> Node;
public:
    Node* search(const K& key){return _search(_root);}
    void insert(K key);
    void levelOrderOutput(){_levelOrderOutput(_root);}
private:
    Node* _search(Node* node,const K& key);
    void split_child(Node* node,int index);
    void insert_notfull(Node* node, K& key);
    void _levelOrderOutput(BTreeNode<K,T>* node);
    Node *_root = NULL;
};

template<class K, int T>
BTreeNode<K,T>* BTree<K,T>::_search(BTreeNode<K,T>* node, const K& key)
{
    int i = 1;
    while (i <= node->_size && key > node->_keys[i])
        i++;
    
    if (i <= node->_size && key == node->_keys[i])
        return node;
    else if(node->isLeaf())
        return NULL;
    else
        return _search(node->_children[i],key);
}

template<class K, int T>
void BTree<K,T>::split_child(BTreeNode<K,T>* node, int index)
{
    Node* parent = node;
    Node* rightNode = new Node();
    Node* leftNode = parent->_children[index];
    rightNode->_isLeaf = leftNode->_isLeaf;
    rightNode->_size = T - 1;

    for (int i = 1; i <= T - 1; i++)
        rightNode->_keys[i] = leftNode->_keys[i+T];
    
    if (!(leftNode->_isLeaf))
        for (int i = 1; i <= T; i++)
            rightNode->_children[i] = leftNode->_children[i+T];
    
    leftNode->_size = T - 1;
    
    // 移动并插入parent结点的孩子指针
    for (int i = parent->_size + 1; i >= index + 1; i--)
        parent->_children[i + 1] = parent->_children[i];
    parent->_children[index+1] = rightNode;

    // 移动并插入parent结点的关键字
    for (int i = parent->_size; i >= index; i-- )
        parent->_keys[i + 1] = parent->_keys[i];
    parent->_keys[index] = leftNode->_keys[T];
    parent->_size++;
}

template<class K, int T>
void BTree<K,T>::insert(K key)
{
    Node *curr = _root;
    if (curr == NULL){
        _root = new Node();
        _root->_keys[1] = key;
        _root->_size = 1;
        _root->_isLeaf = true;
        return;
    }
    if (_root->_size == 2 * T - 1){
        Node *newNode = new Node();
        _root = newNode;
        newNode->_isLeaf = false;
        newNode->_size = 0;
        newNode->_children[1] = curr;
        split_child(newNode, 1);
        insert_notfull(newNode,key);
    }
    else
        insert_notfull(curr,key);
}


template<class K, int T>
void BTree<K,T>::insert_notfull(Node* node, K& key)
{
    int i = node->_size;
    if (node->_isLeaf){
        while (i >= 1 && key < node->_keys[i])
        {
            node->_keys[i+1] = node->_keys[i];
            i = i -1;
        }
        node->_keys[i+1] = key;
        node->_size += 1;
    }
    else {
        while (i >= 1 &&  key < node->_keys[i])
            i -= 1;
        if (node->_children[i]->_size == 2*T - 1){
            split_child(node,i);
            if (key > node->_keys[i])
                i = i + 1;
        }
        insert_notfull(node->_children[i],key);
    }
}

template<class K, int T>
void BTree<K,T>::_levelOrderOutput(BTreeNode<K,T>* node)
{
    queue<BTreeNode<K,T>*> q;
    if (node) q.push(node);

    while(!q.empty())
    {
        BTreeNode<K,T>* curr = q.front();
        curr->printNode();
        if (!curr->_isLeaf){
            for (int i = 1; i <= node->_size + 1; i++ )
                q.push(curr->_children[i]);
        }
        q.pop();
    }
}
