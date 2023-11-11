#ifndef __Hash__
#define __Hash__

#include <iostream>
#include <string>

using namespace std;

template <class K> class Hash;

template<>
class Hash<string>
{
public:
    size_t operator()(const string key) const 
    {
        unsigned long hashValue = 0;
        int length = (int) key.length();
        for (int i = 0; i < length; i++)
            hashValue = 5 * hashValue + key.at(i);
        
        return size_t(hashValue);
    }
};

template<>
class Hash<int>
{
public:
    size_t operator()(const int key) const {
        return size_t(key);
    }
};

template<>
class Hash<long>
{
public:
    size_t operator()(const long key) const
    {return size_t(key);}
};

#endif