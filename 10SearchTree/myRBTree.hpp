#pragma once
#include "RBTreeNode.hpp"
#include <iostream>
#include <fstream>   /// for std::ofstream
#include <queue>
#include <cassert>
using namespace std;

template<class K,class V>
class RBTree{
    typedef RBTreeNode<K,V> Node;
public:
    RBTree(){
        _nil = new Node();
        _nil->_col = BLACK;
        _nil->_left = NULL;
        _nil->_right = NULL;
        _nil->_parent = NULL;
        _root = _nil;
    }
    void insert(const pair<K,V>& pair);
    void preOrderOutput(){_preOrder(_root);cout << endl;};
    void inOrderOutput(){_inOrder(_root);cout << endl;};
    void postOrderOutput(){_postOrder(_root);cout << endl;};
    void levelOrderOutput(){_levelOrder(_root);cout << endl;};
    void print(const char *file_name);
    RBTreeNode<K,V>* remove(const K& key);
    RBTreeNode<K,V>* presuccessor(Node *node);
    RBTreeNode<K,V>* root(){return _root;}
    RBTreeNode<K,V>* nil(){return _nil;}
private:
    void _preOrder(Node* node);
    void _inOrder(Node* node);
    void _postOrder(Node* node);
    void _levelOrder(Node* node);

    void removeFixup(Node *node);
    void insertFixup(Node* node);
    void leftRotate(Node* node);
    void rightRotate(Node* node);
    void PrintNode(std::ofstream &ofs, Node *node, int parent_index,
                    int index, int parent_child_index);
    Node *_root;
    Node *_nil;
};

template<class K, class V>
void RBTree<K,V>::insert(const pair<K,V>& pair)
{

    Node *parent = _nil;
    Node *curr = _root;
    while (curr != _nil)
    {
        parent = curr;
        if (pair.first == curr->_kv.first){
            curr->_kv.second = pair.second;
            return ;
        }
        else if (pair.first < curr->_kv.first)
            curr = curr->_left;
        else 
            curr = curr->_right;
    }

    curr = new Node(pair);
    curr->_col = RED;
    curr->_parent = parent;
    curr->_left = _nil;
    curr->_right = _nil;

    if (parent == _nil){
        _root = curr;
        _root->_parent = _nil;
        _root->_left = _nil;
        _root->_right = _nil;
    }    
    else{
        if (curr->_kv.first < parent->_kv.first)
            parent->_left = curr;
        else 
            parent->_right = curr;
    }

    insertFixup(curr);
}

template<class K,class V>
void RBTree<K,V>::insertFixup(Node *node)
{
    // 
    Node* curr = node;
    while (curr->_parent->_col == RED)
    {
        Node* parent = curr->_parent;
        Node* grandParent = parent->_parent;
        // z的父结点是其祖父结点的左孩子
        if (parent == grandParent->_left ){
            Node *uncle = grandParent->_right;
            // case1:
            if(uncle->_col == RED){
                parent->_col = BLACK;
                uncle->_col = BLACK;
                grandParent->_col = RED;
                curr = grandParent; // 上溯
                continue;
            }
            // case2 || case 3
            else {
                if (curr == parent->_right){
                    curr = parent;
                    leftRotate(curr);
                    parent = curr->_parent;
                    grandParent = parent->_parent;
                }
                parent->_col = BLACK;
                grandParent->_col = RED;
                rightRotate(grandParent);
                break;
            }
        }
        else{
            Node *uncle = grandParent->_left;
            if(uncle->_col == RED){
                parent->_col = BLACK;
                uncle->_col = BLACK;
                grandParent->_col = RED;
                curr = grandParent; // 上溯
                continue;
            }
            // case2 || case 3
            else {
                if (curr == parent->_left){
                    curr = parent;
                    rightRotate(curr);
                    parent = curr->_parent;
                }
                parent->_col = BLACK;
                grandParent->_col = RED;
                leftRotate(grandParent);
                break;
            }
        }
    }
    _root->_col = BLACK;
}

template<class K, class V>
void RBTree<K,V>::leftRotate(Node* node){
    Node *childR = node->_right;
    Node *childRchildL = childR->_left;
    Node *parent = node->_parent;

    if(parent == _nil)
        _root = childR;
    else if(parent->_left == node)
        parent->_left = childR;
    else if(parent->_right == node)
        parent->_right = childR;
    childR->_parent = parent;

    node->_right = childRchildL;
    if (childRchildL != _nil)
        childRchildL->_parent = node;
    
    childR->_left = node;
    node->_parent = childR;

}
template<class K, class V>
void RBTree<K,V>::rightRotate(Node* node){
    Node *childL = node->_left;
    Node *childLchildR = childL->_right;
    Node *parent = node->_parent;

    if(parent == _nil)
        _root = childL;
    else if(parent->_left == node)
        parent->_left = childL;
    else if(parent->_right == node)
        parent->_right = childL;
    childL->_parent = parent;

    node->_left = childLchildR;
    if (childLchildR != _nil)
        childLchildR->_parent = node;
    
    childL->_right = node;
    node->_parent = childL;
}

template<class K, class V>
void RBTree<K,V>::_preOrder(Node* node){
    if (node == _nil) return;
    string color = node->_col == 0 ? "R" : "B";
    cout << node->_kv.first <<":" << node->_kv.second <<":" << color <<"  ";
    _preOrder(node->_left);
    _preOrder(node->_right);
}
template<class K, class V>
void RBTree<K,V>::_inOrder(Node* node){
    if (node == _nil) return;
    _inOrder(node->_left);
    string color = node->_col == 0 ? "R" : "B";
    cout << node->_kv.first <<":" << node->_kv.second <<":" << color <<"  ";
    _inOrder(node->_right);
}
template<class K, class V>
void RBTree<K,V>::_postOrder(Node* node){
    if (node == _nil) return;
    _postOrder(node->_left);
    _postOrder(node->_right);
    string color = node->_col == 0 ? "R" : "B";
    cout << node->_kv.first <<":" << node->_kv.second <<":" << color <<"  ";

}
template<class K, class V>
void RBTree<K,V>::_levelOrder(Node* node){

}

template<class K, class V>
void RBTree<K,V>::print(const char *file_name)
{
    if (!file_name) {
        file_name = "out.dot";
    }

    std::ofstream ofs;
    
    ofs.open(file_name);
    if (!ofs) {
        std::cout << "create tree dot file failed, " << file_name << std::endl;
        return;
    }

    ofs << "digraph RBTree {\n";
    ofs << "\tnode [shape=ellipse, style=filled, fontcolor=white]\n";
    ofs << "\tedge [arrowhead=vee]\n";

    std::queue<Node*> q;
    if (_root != _nil) q.push(_root);
    while (!q.empty())
    {
        Node* curr = q.front();
        string color = curr->_col == RED ? "red" : "black";
        ofs <<"\t" << curr->_kv.first <<"\t[color="<<color<<"];\n";
        if (curr->_parent != _nil)
            ofs << "\t" << curr->_parent->_kv.first <<" -> " 
            << curr->_kv.first << "[color=" <<color <<"];\n";

        if (curr->_left != _nil)
            q.push(curr->_left);
        if(curr->_right != _nil)
            q.push(curr->_right);
        
        q.pop();

    }   
    
    ofs << "}\n";
    ofs.close();

}


template<class K, class V>
RBTreeNode<K,V>* RBTree<K,V>::remove(const K& key)
{
    Node* curr = _root;
    while (curr != _nil)
    {
        if(curr->_kv.first == key)
            break;
        else if (key < curr->_kv.first)
            curr = curr->_left;
        else 
            curr = curr->_right;   
    }
    if (curr == _nil) return NULL;

    Node* logicDelNode = curr;
    Node* actualDelNode;
    if (curr->_left == _nil || curr->_right == _nil)
        actualDelNode = logicDelNode;
    else 
        actualDelNode = presuccessor(curr);
    Node* subsNode;
    if (actualDelNode->_left != _nil)
        subsNode = actualDelNode->_left;
    else
        subsNode = actualDelNode->_right;

    subsNode->_parent = actualDelNode->_parent; // 这里subsNode可能是nil

    if (actualDelNode->_parent == _nil)
        _root = subsNode;
    else
        if (actualDelNode == actualDelNode->_parent->_left)
            actualDelNode->_parent->_left = subsNode;
        else
            actualDelNode->_parent->_right = subsNode;
    
    if(logicDelNode != actualDelNode)
        logicDelNode->_kv = actualDelNode->_kv;
    
    if (actualDelNode->_col == BLACK)
        removeFixup(subsNode);  // 这里的subsNode可能是nil

    return actualDelNode;

}

template<class K,class V>
RBTreeNode<K,V>* RBTree<K,V>::presuccessor(Node *node)
{
    assert(node->_left != _nil);

    Node *curr = node->_left;
    while (curr->_right != _nil)
        curr = curr->_right;
    return curr;
}

template<class K,class V>
void RBTree<K,V>::removeFixup(Node *node)
{   
    // node可能为nil，node为nil情况下，nil->parent指向 actualDelNode的parent
    Node *curr = node;
    while (curr != _root && curr->_col == BLACK )
    {
        Node *parent = curr->_parent;
        // case 1~4
        if (curr == parent->_left){
            Node *brother = parent->_right;
            // case1: x的右兄弟w为红色， case1->case2
            if (brother->_col == RED){
                brother->_col = BLACK;
                parent->_col = RED;
                leftRotate(parent);
                brother = parent->_right;
            }

            // cas2: w为黑，w的两个孩子都为黑，parent为红/黑
            if (brother->_left->_col == BLACK && brother->_right->_col == BLACK){
                brother->_col = RED;
                curr = curr->_parent;
                continue;
            }
            // case3,4:w为黑，w的两个孩子至少有一个是红
            else {
                // case3: w为黑，w左红右黑,case3->case4
                if (brother->_right->_col == BLACK ) {
                    brother->_left->_col = BLACK;
                    brother->_col = RED;
                    rightRotate(brother);
                    brother = parent->_right;
                }
                // case4: w为黑，w右红，左可红可黑
                brother->_col = parent->_col;
                parent->_col = BLACK;
                brother->_right->_col = BLACK;
                leftRotate(parent);
                curr = _root;
                break;
            }
        }
        // case 1'~4'
        else {
            Node *brother = parent->_left;
            // case1': x的左兄弟w为红，parent一定为红，case1'->case2'
            if (brother->_col == RED){
                brother->_col = BLACK;
                parent->_col = RED;
                rightRotate(parent);
                brother = parent->_left;
            }

            // case2': x的左兄弟w为黑，w的两个孩子都是黑，parent为红/黑,将w的黑色向上传递
            if (brother->_left->_col == BLACK && brother->_right->_col == BLACK)
            {
                brother->_col = RED;
                curr = curr->_parent;
                continue;
            }
            // case3',4': w为黑，w的两孩子至少有一个是红
            else {
                // case3':w为黑，w左黑右红，case3'->case4'
                if (brother->_left->_col == BLACK){
                    brother->_right->_col = BLACK;
                    brother->_col = RED;
                    leftRotate(brother);
                    brother = parent->_left;
                }

                //case4':w为黑，w左红，w右可红可黑
                brother->_col = parent->_col;
                parent->_col = BLACK;
                brother->_left->_col = BLACK;
                rightRotate(parent);
                curr = _root;
                break;
            }
        }
    }
    curr->_col = BLACK;
}
// void RBTree<K,V>::PrintNode(std::ofstream &ofs, Node *node, int parent_index,
//                 int index, int parent_child_index)
// {
//     assert(node);

//     ofs << 
// }