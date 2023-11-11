#ifndef __LinearList__
#define __LinearList__
#include<iostream>
template<class T>
class LinearList{
public:
    virtual ~LinearList() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& get(int nIndex) const = 0;
    virtual int indexOf(const T& element) const = 0;
    virtual void erase(int nIndex) = 0;
    virtual void insert(int nIndex, const T& element) = 0;
    virtual void output(std::ostream& out) const = 0;
};
#endif