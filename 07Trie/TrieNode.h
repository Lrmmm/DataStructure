#ifndef __TrieNode__
#define __TrieNode__

#include <unordered_map>
#include "../06Hash/HashLink.hpp"
using namespace std;

class TrieNode {
public:
    unordered_map<char,TrieNode*> children;
    bool isWord;
    TrieNode(){
        isWord = false;
    }
    ~TrieNode() {
        for (auto it = children.begin(); it != children.end(); it++)
            delete it->second;
    }
};

#endif