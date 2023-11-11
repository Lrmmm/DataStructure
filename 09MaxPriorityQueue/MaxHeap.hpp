#ifndef __MaxHeap__
#define __MaxHeap__
#include "MaxPriorityQueue.h"
#include "../exception/myException.h"
#include <fstream> 
#include <iostream>
#include <queue>
using namespace std;

template<class T, class Compare = std::less<T>>
class MaxHeap : public MaxPriorityQueue<T>
{
public:
    MaxHeap(int initialCapacity = 10);
    MaxHeap(vector<T>& arry);
    ~MaxHeap(){delete[] heap;}
    bool empty() const {return heapSize == 0;}
    int size() const {return heapSize;}
    const T& top(){
        if (heapSize == 0) throw  HeapEmpty("HeapEmpty");
        return heap[0];
    }
    void pop();
    void push(const T&);
    void initialize(T*,int);
    void output(ostream& out) const;
    void print2Graph(const char *file_name);
private:
    void heapify(int i);
    int parent(int i){return i > 0 ?(i - 1) / 2 : -1;}
    int left(int i){return i*2 + 1;}
    int right(int i){return i*2 + 2;}
    int heapSize;
    int arrayLength;
    T* heap;
    Compare comparer;
};

template<class T, class Compare>
MaxHeap<T,Compare>::MaxHeap(int initialCapacity)
{
    if (initialCapacity < 1) throw illegalParameterValue("illegalParameterValue");
    arrayLength = initialCapacity;
    heap = new T[arrayLength];
    heapSize = 0;
}

template<class T, class Compare>
void MaxHeap<T,Compare>::push(const T& key)
{
    // 线性表扩张动作
    if (heapSize == arrayLength)
    {
        T* temp = new T[arrayLength*2];
        for (int i = 0; i < heapSize; i++)
            temp[i] = heap[i];
        delete heap;
        arrayLength*=2;
        heap = temp;
    }

    // 在堆中插入key
    ++heapSize;
    int i = heapSize - 1; // i 是当前待插入的位置
    while (i != 0 && comparer(heap[parent(i)],key))  // i非根，并且违反根性质时向上调整
    {
        heap[i] = heap[parent(i)];  // 将违反父大子小性质的父结点换下来
        i = parent(i);
    }
    heap[i] = key;
}


template<class T, class Compare>
void MaxHeap<T,Compare>::pop()
{
    if (heapSize == 0)
        throw QueueEmpty("QueueEmpty");
    
    heap[0].~T();
    heapSize--;
    T currElement = heap[heapSize];


    // 自顶向下调整
    int curr = 0;
    int child = left(curr);
    while (child <= heapSize - 1)
    {
        if (child < heapSize - 1 && comparer(heap[child],heap[child + 1]))
            child++;
        
        if (!comparer(currElement, heap[child]))
            break;
        
        heap[parent(child)] = heap[child];
        curr = child;
        child = left(child);
    }
    heap[parent(child)] = currElement;
}

template<class T, class Compare>
void MaxHeap<T,Compare>::initialize(T *theHeap, int theSize)
{
    delete [] heap;
    heap = theHeap;
    heapSize = theSize;

    // 从第一个非叶子结点i开始调整大根堆
    for (int curr = heapSize / 2 - 1; curr >= 0; curr--)
    {
        T currElement = heap[curr];
        int child = left(curr);
        while (child <= heapSize - 1)
        {
            if (child < heapSize - 1 && comparer(heap[child], heap[child+1]))
                child++;
            
            if (!comparer(currElement,heap[child]))
                break;

            heap[parent(child)] = heap[child];
            child = left(child);
        }   
        heap[parent(child)] = currElement;
    }
    
}

template<class T, class Compare>
void MaxHeap<T,Compare>::output(ostream& out) const
{
    for (int i = 0; i < heapSize; i++)
        out << heap[i] << " ";
    
}

template<class T,class Compare>
ostream& operator<<(ostream& out, const MaxHeap<T,Compare>& x)
{
    x.output(out);
    return out;
}


template<class T,class Compare>
void MaxHeap<T,Compare>::print2Graph(const char *file_name)
{
    if (!file_name) {
        file_name = "/home/lirunmin/DataStructure/output/MaxHeap.dot";
    }

    std::ofstream ofs;
    ofs.open(file_name);
    if (!ofs) {
        std::cout << "create tree dot file failed, " << file_name << std::endl;
        return;
    }

    ofs << "digraph MaxHeap {\n";
    ofs << "\tnode [shape=ellipse, style=filled, fontcolor=black]\n";
    ofs << "\tedge [arrowhead=vee]\n";

    std::queue<int> q;
    if (heapSize != 0) q.push(0);
    while (!q.empty())
    {
        int curr = q.front();
        ofs << "\tnode_" << curr << " [label=\"" << heap[curr] <<"\"];\n";
        if (parent(curr) >= 0)
            ofs << "\tnode_" << parent(curr) <<" -> node_" << curr << ";\n";

        if (left(curr) < heapSize)
            q.push(left(curr));
        if (right(curr) < heapSize)
            q.push(right(curr));
        
        q.pop();
    }
    ofs << "}\n";
    ofs.close();
}
#endif