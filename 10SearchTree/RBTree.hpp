#pragma once
#include<iostream>
#include"RBTreeNode.hpp"
using namespace std;

template<class K, class V>
class RBTree{
    typedef RBTreeNode<K,V> Node;
public:
    RBTree(){
        _nil = new RBTreeNode<K,V>();
        _nil->_col = BLACK;
        _nil->_left = NULL;
        _nil->_right = NULL;
        _root = _nil;
    }
    bool insert(const pair<K,V>& kv);
    Node* search(const K& key) { return searchHelper(_root,key);}
    void preOrder() {preOrderHepler(this->_root);}
    void inOrder() {inOrderHepler(this->_root);}
    void postOrder() {postOrderHepler(this->_root);}
    Node* minimum(Node* node);
    Node* maximum(Node* node);
    Node* successor(Node* node);
    Node* predecessor(Node* node);
    void leftRotate(Node* node);
    void rightRotate(Node* node);
    Node* getRoot(){return _root;}
    void deleteNode(const K& key){deleteNodeHelper(_root,key);}
    void print(){printHepler(_root,"", true);}
    Node* root(){return _root;}
    Node* nil(){return _nil;}

private:
    Node* _root;
    Node* _nil;
    void preOrderHepler(Node* node);
    void inOrderHepler(Node* node);
    void postOrderHepler(Node* node);
    Node* searchHelper(Node* node, const K& key);
    void fixDelete(Node* node);
    void rbTransplant(Node* u, Node*v);
    void deleteNodeHelper(Node *node, const K& key);
    void fixInsert(Node *node);
    void printHepler(Node *root, string indent, bool last);
};
