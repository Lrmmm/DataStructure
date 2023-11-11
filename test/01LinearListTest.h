#include "../include/include.h"

void Test01()
{
    // Test01 ArrayList
    ArrayList<int> myArrayList;
    myArrayList.push_back(1);
    myArrayList.push_back(2);
    myArrayList.push_back(3);
    myArrayList.push_back(4);
    myArrayList.push_back(5);
    cout << myArrayList << endl;
    cout << "capacity:" <<myArrayList.capacity() << endl;
    cout << "size:" <<myArrayList.size() << endl;

    // Test01 LinkList
    LinkList<int> myLinkList;
    myLinkList.push_back(1);
    myLinkList.push_back(2);
    myLinkList.push_back(3);
    myLinkList.push_back(4);
    myLinkList.pop();
    cout << myLinkList << endl;
}