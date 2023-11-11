#ifndef __Node234__
#define __Node234__
#include<iostream>
#include<array>
#include<cassert>
#include<memory>
using namespace std;
class Node{
public:
    Node(int item):count(1),items({{item,0,0}}),
        children({{NULL,NULL,NULL,NULL}}){}
    bool isLeaf(){return children[0] == NULL;}
    bool isFull(){return count == 3;}
    bool is2Node(){return count == 1;}
    bool is34Node(){return count == 2 || count == 3;}
    bool contains(int item){
        for (int i = 0; i < count; i++)
            if(item == items[i]) 
                return true;
        return false;
    }
    int getIndex(int item)
    {
        for (int i = 0; i < count; i++)
            if(item == items[i])
                return i;
        return -1;
    }
    int getItem(int index){return items[index];}
    int getMaxItem(){return items[count - 1];}
    int getMinItem(){return items[0];}
    int insertItem(int item){
        assert(!isFull());
        if(contains(item)) return -1;
        int index = 0;
        for (int index = 0; index < count; index++)
            if(item < items[index])
                break;
        insertItemByIndex(index, item, nullptr,true);
        return index;
    }
    void insertItemByIndex(int index, int item, Node*child, bool to_left = true)
    {
        assert(count < 3 && index >= 0 && index < 3);
        for (int i = count - 1; i >= index; i--)
            items[i + 1] = items[i];
        
        items[index] = item;

        int start_index = to_left ? index : index + 1;
        for (int i = count; i >= start_index; i--)
            children[i + 1] = children[i];
        children[start_index] = child;
        count++;
    }
    Node* removeItemByIndex(int index, bool keep_left){
        assert(index >= 0 && index < count);
        Node *removed_child = keep_left ? children[index + 1 ]:children[index];
        for (int i = index; i < count - 1; i++)
            items[i] = items[i + 1];
        
        for (int i = keep_left ? index + 1 : index; i < count; i++)
            children[i] = children[ i + 1];
        
        count--;
        return removed_child;
    }

    int getChildIndex(Node* child){
        for (int i = 0; i < count + 1; i++)
            if (children[i] == child)
                return i;
        return -1;
    }

    Node* getChild(int index){return children[index];}

    void SetChild(int index, Node* child){children[index] = child;}

    Node* getRightMostChild(){return children[count];}

    Node* getLeftMostChild(){return children[0];}

    Node* getItemLeftChild(int index){
        if (index < 0 || index > count - 1)
            return NULL;
        return children[index];
    }
    Node* getItemRightChild(int index){
        if (index < 0 || index > count - 1) return NULL;
        return children[index + 1];
    }
    Node* getNextPossibleChild(int item){
        int i = 0;
        for ( i = 0; i < count; i++)
            if (item < items[i])
                break;
        return children[i];
    }
    void setCount(int c) {count = c;}
    int getCount(){return count;}
    void setItem(int index, int new_item){
        assert(index >= 0 && index <= 2);
        items[index] = new_item;
    }
    int GetItemIndex(int item) {
        for (int i = 0; i < count; i++) {
            if (items[i] == item) {
                return i;
            }
        }
        return -1;
    }
private:
    array<int,3> items;
    array<Node*,4> children;
    int count;
};

class Tree234{
public:
    Tree234() = default;
    Tree234(const Tree234 &) = delete;
    Tree234(const Tree234 &&) = delete;
    Tree234 &operator=(const Tree234 &) = delete;
    Tree234 &operator=(const Tree234 &&) = delete;
    ~Tree234();
    void insert(int item);
    bool remove(int item);
    void traverse();
    void output(const char* file_name = NULL);
private:
    Node* root{nullptr};

    void insertPreSplit(int item);

    void insertPostMerge(int item);

    Node* insert(Node *tree, int item);

    Node* mergeNode(Node *dst_node, Node* node);

    void mergeNodeNotFull(Node *dst_node, Node* node);

    Node *splitNode(Node *node);

    int getTreeMaxItem(Node *tree);

    int getTreeMinItem(Node *tree);

    bool tryLeftRotate(Node *parent, Node *to_child);

    bool tryRightRotate(Node *parent, Node *to_child);

    void rightRotate(Node* parent, int index);

    void leftRotate(Node *parent, int index);

    bool removePreMerge(Node* node, int item);

    Node *merge(Node *parent, int index);

    void deleteNode(Node *tree);

    void traverse(Node *tree);

    void printNode(ofstream &ofs, Node *node, int parent_index,
                    int index, int parent_child_index);
    

};

Tree234::~Tree234(){deleteNode(root);}

void Tree234::deleteNode(Node *tree)
{
    if (!tree) return;
    for (int i = 0; i <= tree->getCount(); i++)
    {
        deleteNode(tree->getChild(i));
    }
    
    delete tree;
}

void Tree234::traverse(){
    traverse(root);
    cout << endl;
}

void Tree234::traverse(Node* node){
    if (!node) return;

    int i = 0;
    for ( i = 0; i < node->getCount(); i++)
    {
        traverse(node->getChild(i));
        cout << node->getItem(i) << ", ";
    }
    traverse(node->getChild(i));
}

void Tree234::insertPreSplit(int item)
{
    if (!root){
        root = new Node(item);
        return;
    }

    Node *parent = NULL;
    Node *node = root;

    while (true)
    {
        if (!node){
            unique_ptr<Node> tmp(new Node(item));
            mergeNodeNotFull(parent, tmp.get());
            return;
        }

        if(node->contains(item)) 
            return;
        
        if (node->isFull()){
            node = splitNode(node);

            Node *cur_node = NULL;

            if (item < node->getItem(0))
                cur_node = node->getChild(0);
            else
                cur_node = node->getChild(1);

            if (!parent)
                root = node;
            else
                mergeNodeNotFull(parent,node);
            node = cur_node;
        }
        parent = node;
        node = parent->getNextPossibleChild(item);
    }
}

void Tree234::insertPostMerge(int item)
{
    if (!root) {
        root = new Node(item);
        return ;
    }

    Node *split_node = insert(root,item);

    if (split_node)
        root = split_node;
}

void Tree234::insert(int item)
{
    insertPreSplit(item);
}


Node* Tree234::insert(Node* tree, int item)
{
    assert(tree != NULL);

    std::unique_ptr<Node> split_node;

    if(tree->contains(item)) 
        return NULL;
    
    Node* next_node = tree->getNextPossibleChild(item);
    if (next_node)
        split_node.reset(insert(next_node,item));
    else
        split_node.reset(new Node(item));
    
    if (split_node)
        return mergeNode(tree,split_node.get());
    
    return NULL;
}


Node* Tree234::mergeNode(Node *dst_node, Node *node)
{
    assert(dst_node != NULL && node != NULL);

    if (!dst_node->isFull()) {
        mergeNodeNotFull(dst_node, node);
        return NULL;
    }

    dst_node = splitNode(dst_node);

    if (node->getItem(0) < dst_node->getItem(0)) 
        mergeNodeNotFull(dst_node->getChild(0),node);
    else 
        mergeNodeNotFull(dst_node->getChild(1),node);

    return dst_node;
}

void Tree234::mergeNodeNotFull(Node *dst_node , Node *node)
{
    assert(dst_node && node && !dst_node->isFull() && node->is2Node());

    int i = dst_node->insertItem(node->getItem(0));

    dst_node->SetChild(i, node->getChild(0));
    dst_node->SetChild(i + 1, node->getChild(1));
}

Node* Tree234::splitNode(Node* node)
{
    assert(node->getCount() == 3);

    Node *left = node;
    Node *right = new Node(node->getItem(2));
    right->SetChild(0, node->getChild(2));
    right->SetChild(1, node->getChild(3));
    Node *parent = new Node(node->getItem(1));
    parent->SetChild(0,left);
    parent->SetChild(1,right);

    left->setCount(1);

    return parent;
}

bool Tree234::tryLeftRotate(Node* parent, Node* to_child)
{
    int to_child_index = parent->getChildIndex(to_child);

    if(to_child_index >= parent->getCount())
        return false;

    Node *right_sibling = parent->getChild(to_child_index+1);

    if(right_sibling->is2Node()) 
        return false;
    
    leftRotate(parent,to_child_index);

    return true;
}

bool Tree234::tryRightRotate(Node *parent, Node *to_child)
{
    int to_child_index = parent->getChildIndex(to_child);

    if (to_child_index <= 0)
        return false;
    
    Node *left_sibling = parent->getChild(to_child_index - 1);

    if(left_sibling->is2Node())
        return false;
    
    rightRotate(parent, to_child_index - 1);

    return true;
}

void Tree234::rightRotate(Node *parent, int index)
{
    Node *left = parent->getItemLeftChild(index);
    Node *right = parent->getItemRightChild(index);

    assert(left && left->is34Node());
    assert(right && right->is2Node());

    right->insertItemByIndex(0, parent->getItem(index),
                            left->getRightMostChild(),true);
    parent->setItem(index,left->getMaxItem());
    left->removeItemByIndex(left->getCount() - 1, true);
}

void Tree234::leftRotate(Node *parent, int index)
{
    Node *left = parent->getItemLeftChild(index);
    Node *right = parent->getItemRightChild(index);
    assert(right && right->is34Node());
    assert(left && left->is2Node());
    left->insertItemByIndex(left->getCount(), parent->getItem(index),
                            right->getLeftMostChild(), false);
    parent->setItem(index, right->getMinItem());
    right->removeItemByIndex(0, false);
}

Node *Tree234::merge(Node *parent, int index)
{
    assert(parent);

    Node *left_child = parent->getItemLeftChild(index);
    Node *right_child = parent->getItemRightChild(index);

    assert(left_child->is2Node() && right_child->is2Node());

    int item = parent->getItem(index);

    left_child->setItem(1, item);
    left_child->setItem(2, right_child->getItem(0));
    left_child->SetChild(2,right_child->getChild(0));
    left_child->SetChild(3,right_child->getChild(1));

    left_child->setCount(3);

    parent->removeItemByIndex(index, true);

    delete right_child;
    
    return left_child;
}

bool Tree234::remove(int item){return removePreMerge(root, item);}

bool Tree234::removePreMerge(Node *node, int item)
{
    while (node)
    {
        if (node->isLeaf()) {
            if (node->contains(item)){
                if (node->is2Node()) {
                    delete node;
                    root = NULL;
                }
                else
                    node->removeItemByIndex(node->GetItemIndex(item),true);
                return true;
            }
            return false;
        }

        if (node->contains(item)) {
            int index = node->GetItemIndex(item);
            Node *left_child = node->getItemLeftChild(index);
            Node *right_child = node->getItemRightChild(index);
            assert(left_child && right_child);

            if (left_child->is2Node() && right_child->is2Node())
            {
                if (node->is2Node()){
                    Node *new_root = merge(node, index);
                    delete root;
                    root = new_root;
                    node = root;
                    continue;
                };

                do {
                    if (index > 0)
                    {
                        Node *left_sibling = node->getItemLeftChild(index-1);
                        if(left_sibling->is34Node()) {
                            rightRotate(node, index - 1);
                            break;
                        }
                    }

                    if (index < node->getCount() - 1){
                        Node *right_sibling = node->getItemRightChild(index + 1);
                        if(right_sibling->is34Node())
                        {
                            leftRotate(node, index + 1);
                            break;
                        }
                    }

                    if (index > 0) {
                        merge(node, index - 1);
                        break;
                    }

                    merge(node, index+1);
                }while(false);
            }

            left_child = node->getItemLeftChild(index);
            right_child = node->getItemRightChild(index);

            if (left_child->is34Node())
            {
                int predecessor_item = getTreeMaxItem(left_child);
                node->setItem(node->GetItemIndex(item),predecessor_item);

                node = left_child;
                item = predecessor_item;
                continue;
            }

            if(right_child->is34Node()) {
                int successor_item = getTreeMinItem(right_child);
                node->setItem(node->GetItemIndex(item),successor_item);
                node = right_child;
                item = successor_item;
                continue;
            }
        }

        Node *next_node = node->getNextPossibleChild(item);

        if(next_node->is34Node()) {
            node = next_node;
            continue;
        }

        if(tryRightRotate(node, next_node)){
            node = next_node;
            continue;
        }

        if(tryLeftRotate(node, next_node)){
            node = next_node;
            continue;
        }

        int child_index = node->getChildIndex(next_node);
        if (child_index > 0 )
            node = merge(node, child_index -1);
        else
            node = merge(node,child_index);
    }
    return false;
}

int Tree234::getTreeMaxItem(Node *tree)
{
    assert(tree);
    int max = 0;
    while (tree)
    {
        max = tree->getMaxItem();
        tree = tree->getRightMostChild();
    }
    return max;
}

#endif
