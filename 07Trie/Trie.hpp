#ifndef __Trie__
#define __Trie__

#include "../01LinearList/ArrayList.hpp"
#include "TrieNode.h"
#include <unordered_map>
using namespace std;
class Trie{
private:
    TrieNode* root;
public:
    Trie() {root = new TrieNode();}
    ~Trie() {delete root;}
    void insert(string word);
    bool search(string word);
    bool prefixSearch(string word);
};

void Trie::insert(string word)
{
    TrieNode *p = root;
    for (int i = 0; i < (int)word.size(); i++)
    {
        if (p->children.find(word[i]) == p->children.end())
            p->children[word[i]] = new TrieNode();
        p = p->children[word[i]];
    }
    p->isWord = true;
}

bool Trie::search(string word)
{
    TrieNode *p = root;
    for (int i = 0; i < (int)word.size(); i++)
    {
        if (p->children.find(word[i]) == p->children.end())
            return false;
        p = p->children[word[i]];
    }
    return p->isWord;
}

bool Trie::prefixSearch(string word)
{
    TrieNode *p = root;
    for (int i = 0; i < (int)word.size(); i++)
    {
        if (p->children.find(word[i]) == p->children.end())
            return false;
        p = p->children[word[i]];
    }
    return true;
}

#endif