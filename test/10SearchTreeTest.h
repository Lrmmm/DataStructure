
#include "../10SearchTree/AVLTreeNode.h"
#include "../10SearchTree/BinarySearchTree.hpp"
#include "../10SearchTree/Tree234.hpp"
#include "../10SearchTree/AVLTree.hpp"
#include "../10SearchTree/myRBTree.hpp"
#include "../10SearchTree/BTree.hpp"
#include <cstdlib>
#include<iostream>
using namespace std;
using namespace data_structures::tree_234;

// #define __Test_10_1__     // BinarySearchTree
// #define __Test_10_2__     // AVLTree
// #define __Test_10_3__     // 234Tree
#define __Test_10_4__     // RBTree
// #define __Test_10_5__     // BTree
void Test10()
{
#ifdef __Test_10_1__
    BinarySearchTree<int,char> y;
    y.insert(pair<int, char>(1, 'a'));
    y.insert(pair<int, char>(6, 'c'));
    y.insert(pair<int, char>(4, 'b'));
    y.insert(pair<int, char>(8, 'd'));
    cout << "Tree size is " << y.size() << endl;
    cout << "Elements in ascending order are" << endl;
    y.ascend();
    pair<const int, char> *s = y.find(4);
    cout << "Search for 4 succeeds " << endl;
    cout << s->first << ' ' << s->second << endl;
    y.erase(4);
    cout << "4 deleted " << endl;
    cout << "Tree size is " << y.size() << endl;
    cout << "Elements in ascending order are" << endl;
    y.ascend();

    s = y.find(8);
    cout << "Search for 8 succeeds " << endl;
    cout << s->first << ' ' << s->second << endl;
    y.erase(8);
    cout << "8 deleted " << endl;
    cout << "Tree size is " << y.size() << endl;
    cout << "Elements in ascending order are" << endl;
    y.ascend();

    s = y.find(6);
    cout << "Search for 6 succeeds " << endl;
    cout << s->first << ' ' << s->second << endl;
    y.erase(6);
    cout << "6 deleted " << endl;
    cout << "Tree size is " << y.size() << endl;
    cout << "Elements in ascending order are" << endl;
    y.ascend();

    s = y.find(1);
    cout << "Search for 1 succeeds " << endl;
    cout << s->first << ' ' << s->second << endl;
    y.erase(1);
    cout << "1 deleted " << endl;
    cout << "Tree size is " << y.size() << endl;
    cout << "Elements in ascending order are" << endl;
    y.ascend();
#endif
#ifdef __Test_10_2__
    AVLTree<int,char> y;
    y.insert(pair<int, char>(4, 'a'));
    y.insert(pair<int, char>(2, 'a'));
    y.insert(pair<int, char>(6, 'a'));
    y.insert(pair<int, char>(1, 'a'));
    y.insert(pair<int, char>(3, 'a'));
    y.insert(pair<int, char>(5, 'a'));
    y.insert(pair<int, char>(15, 'a'));
    y.insert(pair<int, char>(7, 'a'));
    y.insert(pair<int, char>(16, 'a'));
    y.insert(pair<int, char>(14 ,'a'));
    y.remove(16);
    y.remove(6);
    // y.remove(4);
    // y.remove(1);
    // y.remove(3);
    // y.remove(2);
    // y.remove(14);
    // y.remove(5);
    // y.remove(15);
    y.preOrderOutput();
    y.levelOrderOutput();
    y.inOrderOutput();
#endif
#ifdef __Test_10_3__
    data_structures::tree_234::Tree234 tree;

    // std::vector<char> arr = {'A','S','E','R','C','D','I','N','B','X'};

    // for (auto i : arr) {
    //     int64_t item = static_cast<int64_t>(i - 'A');
    //     tree.Insert(item);
    // }
    // tree.PrintStr();
    vector<int64_t> arr = {8,18,5,15,17,25,40,80};
    for (auto i : arr)
        tree.Insert(i);
    tree.Remove(25);
    tree.Print();

#endif
#ifdef __Test_10_4__ 
    Tree234* myTree234;
    RBTree<int,string> myRBTree;
    // char str;
    myRBTree.insert(make_pair<int,string>(8,"lrm"));
    // cin >> str;
    myRBTree.print("/home/lirunmin/DataStructure/output/RBTree.dot");
    myRBTree.insert(make_pair<int,string>(18,"lrm"));
    // cin >> str;
    myRBTree.print("/home/lirunmin/DataStructure/output/RBTree.dot");
    myRBTree.insert(make_pair<int,string>(5,"lrm"));
    // cin >> str;
    myRBTree.print("/home/lirunmin/DataStructure/output/RBTree.dot");
    myRBTree.insert(make_pair<int,string>(15,"lrm"));
    // cin >> str;
    myRBTree.print("/home/lirunmin/DataStructure/output/RBTree.dot");
    myRBTree.insert(make_pair<int,string>(17,"lrm"));
    // cin >> str;
    myRBTree.print("/home/lirunmin/DataStructure/output/RBTree.dot");
    myRBTree.insert(make_pair<int,string>(25,"lrm"));
    // cin >> str;
    myRBTree.print("/home/lirunmin/DataStructure/output/RBTree.dot");
    myRBTree.insert(make_pair<int,string>(40,"lrm"));
    // cin >> str;
    myRBTree.print("/home/lirunmin/DataStructure/output/RBTree.dot");
    myRBTree.insert(make_pair<int,string>(80,"lrm"));
    myRBTree.insert(make_pair<int,string>(3,"lrm"));
    myRBTree.insert(make_pair<int,string>(36,"lrm"));
    myRBTree.insert(make_pair<int,string>(55,"lrm"));
    myRBTree.insert(make_pair<int,string>(10,"lrm"));
    myRBTree.insert(make_pair<int,string>(9,"lrm"));

    myTree234 = new Tree234(myRBTree);
    myTree234->Print("/home/lirunmin/DataStructure/output/Tree234.dot");
    myRBTree.print("/home/lirunmin/DataStructure/output/RBTree.dot");
    delete myTree234;

    myRBTree.remove(25);
    myTree234 = new Tree234(myRBTree);
    myTree234->Print("/home/lirunmin/DataStructure/output/Tree234Del.dot");
    myRBTree.print("/home/lirunmin/DataStructure/output/RBTreeDel.dot");
    delete myTree234;
    myRBTree.inOrderOutput();

#endif

#ifdef __Test_10_5__
    BTree<char,3> myBTree;
    myBTree.insert('A');
    myBTree.insert('B');
    myBTree.insert('C');
    myBTree.insert('D');
    myBTree.insert('E');
    myBTree.insert('G');
    myBTree.insert('M');
    myBTree.insert('J');
    myBTree.insert('K');
    myBTree.insert('L');
    myBTree.insert('N');
    myBTree.insert('O');
    myBTree.insert('P');
    myBTree.insert('T');
    myBTree.insert('X');
    myBTree.insert('Q');
    myBTree.insert('R');
    myBTree.insert('S');
    myBTree.insert('U');
    myBTree.insert('V');
    myBTree.insert('Y');
    myBTree.insert('Z');


    myBTree.levelOrderOutput();
#endif
}