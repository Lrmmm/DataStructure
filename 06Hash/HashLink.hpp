#ifndef __HashLink__
#define __HashLink__

#include <iostream>
#include "Hash.h"
#include "../05Dictionary/Dictionary.h"
#include "../01LinearList/SortedLinkList.hpp"

using namespace std;

template<class K, class V>
class HashLink : public Dictionary<K,V>{
public:
    HashLink(int theDivisor = 11 )
    {
        nDivisor = theDivisor;
        nSize = 0;
        table = new SortedLinkList<K,V>[nDivisor];
    }

    ~HashLink(){
        delete[] table;
    }

    bool empty() const { return nSize == 0;}
    int size() const {return nSize;}

    pair<const K,V>* find(const K& theKey) const
    {
        return table[hash(theKey) % nDivisor].find(theKey);
    }

    void insert(const pair<const K, V>& thePair)
    {
        int homeBucket = (int) hash(thePair.first) % nDivisor;
        int homeSize = table[homeBucket].size();
        table[homeBucket].insert(thePair);
        if (table[homeBucket].size() > homeSize)
            nSize++;
    }

    void erase(const K& theKey)
    {
        table[hash(theKey) % nDivisor].erase(theKey);
    }

    void output(ostream& out) const
    {
        for (int i = 0; i < nDivisor; i++)
        {
            if (table[i].size() == 0)
                out << "NULL" << " ";
            else 
                out << table[i] << " ";
        }
        
    }

protected:
    SortedLinkList<K,V>* table;
    Hash<K> hash;
    int nSize;
    int nDivisor;
};

template<class K, class V>
ostream& operator<<(ostream& out, const HashLink<K,V>& x)
{
    x.output(out);
    return out;
}

#endif