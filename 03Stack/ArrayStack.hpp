#ifndef __ArrayStack__
#define __ArrayStack__
#include "./Stack.h"
#include "../exception/myException.h"
template<class T>
class ArrayStack : public Stack<T>
{
public:
    ArrayStack(int initCapacity = 1);
    ~ArrayStack(){delete[] stack;}
    bool empty() const {return nTop == -1;}
    int size() const {return nTop + 1;}
    T& top(){
        if (nTop == -1)
            throw StackEmpty("StackEmpty");
        return stack[nTop];
    }
    void pop(){
        if (nTop == -1)
            throw StackEmpty("StackEmpty");
        stack[nTop--].~T();
    }
    void push(const T& elem);
private:
    int nTop;
    int length;
    T* stack;
};

template<class T>
ArrayStack<T>::ArrayStack(int initCapacity)
{
    if (initCapacity < 1)
        throw illegalParameterValue("illegalParameterValue");
    
    length = initCapacity;
    stack = new T[length];
    nTop = -1;
}

template<class T>
void ArrayStack<T>::push(const T& elem) 
{
    if (nTop == length - 1) {
        T* temp = new T[length * 2];
        for (int i = 0; i < nTop; i++)
            temp[i] = stack[i];
        delete stack;
        length *= 2;
        stack = temp;
    }
    stack[++nTop] = elem;
}
#endif