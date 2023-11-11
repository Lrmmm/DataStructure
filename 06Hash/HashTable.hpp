#pragma once
#include <iostream>
#include "Hash.h"
#include "../exception/myException.h"

using namespace std;

template<class K, class V>
class HashTable
{
public:
    HashTable(int theDivisor = 11);
    ~HashTable(){delete [] table;}

    bool empty() const {return nSize == 0;}
    int size() const {return nSize;}
    pair<const K, V>* find(const K&) const;
    void insert(const pair<const K, V>&);
    void output(ostream& out) const;
protected:
    int search(const K&) const;
    pair<const K, V>** table;
    Hash<K> hash;
    int nSize;
    int nDivisor;
};

template<class K,class V>
HashTable<K,V>::HashTable(int theDivisor)
{
    nDivisor = theDivisor;
    nSize = 0;
    
    // 分配并初始化Hash Table数组
    table = new pair<const K,V>* [nDivisor];
    for (int i = 0; i < nDivisor; i++)
        table[i] = NULL;
}

template<class K, class V>
int HashTable<K,V>::search(const K& theKey) const
{
    int i = (int) hash(theKey) % nDivisor;
    int j = i;
    do
    {
        if (table[j] == NULL || table[j]->first == theKey)
            return j;
        j = (j + 1)%nDivisor;
    } while (j != i);
    
    return j;
}

template<class K, class V>
pair<const K, V>* HashTable<K,V>::find(const K& theKey) const
{
    int b = search(theKey);

    if (table[b] == NULL || table[b]->first != theKey)
        return NULL;
    
    return table[b];
}

template<class K, class V>
void HashTable<K,V>::insert(const pair<const K, V>& thePair)
{
    int b = search(thePair.first);

    if (table[b] == NULL)
    {
        table[b] = new pair<const K,V>(thePair);
        nSize++;
    }
    else {
        if (table[b]->first == thePair.first)
        {
            table[b]->second == thePair.second;
        }
        else 
            throw HashTableFull("hashTableFull");
    }
}

template<class K, class V>
void HashTable<K,V>::output(ostream& out) const
{
    for (int i = 0; i < nDivisor; i++)
    {
        if (table[i] == NULL)
            out << "NULL" << endl;
        else 
            cout << table[i]->first << "," << table[i]->second << endl;
    } 
    
}

template <class K, class V>
ostream& operator<<(ostream& out, const HashTable<K,V>& x)
{  
    x.output(out);
    return out;
}