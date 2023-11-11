#include "../include/include.h"
void Test07()
{
    Trie myTrie;
    myTrie.insert("lrmlovexhy");
    myTrie.insert("xhylovelrm");
    cout << myTrie.search("xhylovelrmaa") << endl;
}