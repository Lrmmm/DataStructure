#pragma once
#include <iostream>
using namespace std;
enum Color{
    RED,
    BLACK
};

template<class K, class V>
struct RBTreeNode
{
    RBTreeNode<K,V> *_left;
    RBTreeNode<K,V> *_right;
    RBTreeNode<K,V> *_parent;

    pair<K,V> _kv;
    Color _col;

    RBTreeNode(const pair<K,V>& kv):
        _left(NULL),
        _right(NULL),
        _parent(NULL),
        _kv(kv),
        _col(RED){}
    RBTreeNode(){};
};

