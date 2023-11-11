#include "../include/include.h"
void Test08()
{
    // BinaryTreeNode<int>* node = new BinaryTreeNode<int>(1,NULL,NULL);
    BinaryTreeNode<int> *root = new BinaryTreeNode<int>(1, 
    new BinaryTreeNode<int>(2, 
            new BinaryTreeNode<int>(4, NULL, NULL), 
            new BinaryTreeNode<int>(5,new BinaryTreeNode<int>(7,NULL,NULL),NULL)) , 
    new BinaryTreeNode<int>(3,new BinaryTreeNode<int>(6,NULL,NULL),NULL));
    LinkedBinaryTree<int> myTree(root);
    myTree.levelOrderOutput();
    myTree.preOrderOutput();

    LinkedBinaryTree<int> a,x,y,z;
    y.makeTree(1,a,a);
    z.makeTree(2,a,a);
    x.makeTree(3,y,z);
    y.makeTree(4,x,a);
    cout << "Number of nodes = ";
    cout << y.size() << endl;
    cout << "height = ";
    cout << y.height() << endl;
    cout << "Preorder sequence is ";
    y.preOrderOutput();
    cout << "Inorder sequence is ";
    y.inOrderOutput();
    cout << "Postorder sequence is ";
    y.postOrderOutput();
    cout << "Level order sequence is ";
    y.levelOrderOutput();
    auto myVisit = [](BinaryTreeNode<int>* p){
        p->element = 1;
    };
    y.setFuncPointer(myVisit);
    y.postOrder(myVisit);
    y.inOrderOutput();
}