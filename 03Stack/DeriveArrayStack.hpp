#ifndef __DeriveArrayStack__
#define __DeriveArrayStack__
#include <iostream>
#include "../01LinearList/ArrayList.hpp"
#include "../exception/myException.h"
#include "./Stack.h"
using namespace std;
template<class T>
class DeriveArrayStack : public ArrayList<T>,public Stack<T>{
public:
    DeriveArrayStack(int initCapacity = 10) : ArrayList<T> (initCapacity) {}

    bool empty() const {return ArrayList<T>::empty();}
    int size() const {return ArrayList<T>::size();}
    T& top(){
        if (ArrayList<T>::empty())
            throw StackEmpty("StackEmpty");
        return ArrayList<T>::get(ArrayList<T>::size() - 1);
    }
    void pop()
    {
        if (ArrayList<T>::empty())
            throw StackEmpty("StackEmpty");
        ArrayList<T>::erase(ArrayList<T>::size() - 1);
    }

    void push(const T& elem)
    {
        ArrayList<T>::insert(ArrayList<T>::size(), elem);
    }
};

#endif