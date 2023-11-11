#ifndef __LinkedQueue__
#define __LinkedQueue__
#include "Queue.h"
#include "../exception/myException.h"
#include <iostream>
using namespace std;

template<class T>
class LinkedQueue : public Queue<T>
{
public:
    struct Node {
        T data;
        Node *next;
        Node(const T& data) {this->data = data;}
        Node(const T& data, Node* next) {this->data = data; this->next = next;}
    };
    LinkedQueue(int initialCapacity = 0)
        {queueFront = NULL; queueSize = 0;}
    ~LinkedQueue();
    bool empty() const 
        {return queueSize == 0;}
    int size() const
        {return queueSize;}
    T& front()
        {
        if (queueSize == 0)
            throw QueueEmpty("QueueEmpty");
        return queueFront->data;
        }
    T& back()
        {
        if (queueSize == 0)
            throw QueueEmpty("QueueEmpty");
        return queueBack->data;
        }
    void pop();
    void push(const T&);
    void output(ostream& out) const  {
        Node* p = queueFront;
        while(p) {
            out << p->data << " ";
            p = p->next;
        }
    }
    friend ostream& operator<<(ostream& out, const LinkedQueue<T>& x) {
        x.output(out);
        return out;
    }
private:
    Node* queueFront;  // pointer to queue front
    Node* queueBack;   // pointer to queue back
    int queueSize;             // number of elements in queue
};

template<class T>
LinkedQueue<T>::~LinkedQueue()
{
    while (queueFront != NULL) {
        Node* p = queueFront->next;
        delete queueFront;
        queueFront = p;
    }
}

template<class T>
void LinkedQueue<T>::pop()
{
    if (queueFront == NULL)
      throw QueueEmpty("QueueEmpty");
    Node* p = queueFront->next;
    delete queueFront;
    queueFront = p;
    queueSize--;
    
}

template<class T>
void LinkedQueue<T>::push(const T& elem)
{
    Node *newNode = new Node(elem, NULL);
    if (empty()) {
        queueBack = newNode;
        queueFront = newNode;
    }
    else {
        queueBack->next = newNode;
    }

    queueBack = newNode;

}

#endif
