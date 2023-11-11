#ifndef __ArrayQueue__
#define __ArrayQueue__
#include "Queue.h"
#include "../exception/myException.h"
#include <iostream>
using namespace std;
template<class T>
class ArrayQueue : public Queue<T>{
public:
    ArrayQueue(int initCapacity = 1);
    ~ArrayQueue(){delete[] queue;};
    bool empty() const {return nFront == nBack;}
    int size() const {return (nBack - nFront) % nLength;}
    T& front() {
        if (empty())
            throw QueueEmpty("QueueEmpty");
        return queue[(nFront + 1) % nLength];
    }
    T& back() {
        if (empty())
            throw QueueEmpty("QueueEmpty");
        return queue[nBack]; 
    }

    void pop() {
        if (empty())
            throw QueueEmpty("QueueEmpty");
        nFront = (nFront + 1) % nLength;
        queue[nFront].~T();
    }
    void push(const T& elem);
    void output(ostream& out) const {
        for (int i = nFront; i != nBack; i = (i + 1) % nLength)
        {
            out << queue[(i + 1) % nLength] << " ";
        }
        
    }

    friend ostream& operator<<(ostream& out,const  ArrayQueue<T>& x) {
        x.output(out);
        return out;
    }
private:
    int nFront;
    int nBack;
    int nLength;
    T* queue;
};

template<class T>
ArrayQueue<T>::ArrayQueue(int initCapacity)
{
    if (initCapacity < 1)
        throw illegalParameterValue("illegalParameterValue");
    
    nLength = initCapacity;
    queue = new T[nLength];
    nFront = 0;
    nBack = 0;
}

template<class T>
void ArrayQueue<T>::push(const T& elem)
{
    if ((nBack + 1) % nLength == nFront)
    {
        T* newQueue = new T[nLength * 2];
        int start = nFront ;
        int i = 0;
        while (start != nBack) {
            newQueue[i] = queue[(start + 1) % nLength];
            start = (start + 1) % nLength;
            i++;
        }
        nFront = 2 * nLength - 1;
        nBack = nLength - 2;
        nLength *= 2;
        delete[] queue;
        queue = newQueue;
    }

    nBack = (nBack + 1) % nLength;
    queue[nBack] = elem;
}
#endif