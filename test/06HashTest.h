#include "../include/include.h"
void Test06()
{
    // Test HashTable
    HashTable<string, string> myHash;
    myHash.insert(make_pair("lrm","lrm"));
    myHash.insert(make_pair("xxhy","xxhy"));
    myHash.insert(make_pair("xwq","xwq"));
    myHash.insert(make_pair("xhy","xhy"));
    cout << myHash << endl;

    // Test SortedLinkList
    SortedLinkList<int,string> mySortedList;
    mySortedList.insert(make_pair(4,"xwq"));
    mySortedList.insert(make_pair(1,"lm"));
    mySortedList.insert(make_pair(3,"xhy"));
    mySortedList.insert(make_pair(2,"lrm"));
    cout << mySortedList << endl;

    // Test HashLink
    HashLink<int, string> myHashLink;
    myHashLink.insert(make_pair(4,"xwq"));
    myHashLink.insert(make_pair(1,"lm"));
    myHashLink.insert(make_pair(3,"xhy"));
    myHashLink.insert(make_pair(2,"lrm"));
    myHashLink.insert(make_pair(12,"lrm"));
    cout << myHashLink << endl;
}