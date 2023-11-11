#ifndef __MaxPriorityQueue__
#define __MaxPriorityQueue__
template<class T>
class MaxPriorityQueue{
public:
    virtual ~MaxPriorityQueue(){};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual const T& top() = 0;
    virtual void pop() = 0;
    virtual void push(const T& theElement) = 0; 
};
#endif