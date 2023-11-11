#ifndef __ArrayList__
#define __ArrayList__
// #include<sstream>
// #include<algorithm>
#include<iostream>
#include "LinearList.h"
#include "../exception/myException.h"

template<class T>
class ArrayList : public LinearList<T>
{
public:
    ArrayList(int initCapacity = 1);
    ArrayList(const ArrayList<T>&);
    ~ArrayList() {delete [] elements;};


    // Override
    bool empty() const override {return nSize == 0;}
    int size() const override {return nSize;}
    T& get(int nIndex) const override;
    int indexOf(const T& element) const override;
    void erase(int nIndex) override;
    void insert(int nIndex, const T& element) override;
    void output(std::ostream& out) const override;

    //
    int capacity() const {return nLength;};
    friend std::ostream& operator<<(std::ostream& out, const ArrayList<T>& array) {
        array.output(out);
        return out;
    }
    

    void push_back(const T& elem);

protected:
    void checkIndex(int nIndex) const;
    T* elements;
    int nLength;
    int nSize;
};



template<class T>
ArrayList<T>::ArrayList(int initCapacity)
{
    if (initCapacity < 0)
    {
        throw illegalParameterValue("illegalIndex");
    }
    nLength = initCapacity;
    elements = new T[nLength];
    nSize = 0;
}

template<class T>
ArrayList<T>::ArrayList(const ArrayList<T>& souceList)
{
    nLength = souceList.nLength;
    nSize = souceList.nLength;
    elements = new T[nLength];
    for (int i = 0; i < nSize; i++)
        elements[i] = souceList.elements[i];
}

template<class T>
void ArrayList<T>::checkIndex(int nIndex) const {
    if (nIndex < 0 || nIndex >= nSize)
    {
        throw illegalIndex("illegalIndex");
    }
}

template<class T>
T& ArrayList<T>::get(int nIndex) const
{
    checkIndex(nIndex);
    return elements[nIndex];
}

template<class T>
int ArrayList<T>::indexOf(const T& element) const
{
    // search for theElement
    for (int i = 0; i < nSize; i++)
        if (elements[i] == element)
            return i;

    // theElement not found
    return -1;
}

template<class T>
void ArrayList<T>::erase(int nIndex)
{
    checkIndex(nIndex);

    for (int i = nIndex + 1; i < nSize; i++)
        elements[i-1] = elements[i];
    nSize--;
    elements[nSize].~T();
    

    if (nSize != 0 && nSize < nLength / 4) {
        nLength = nLength / 2;
        T* newElements = new T[nLength];
        for (int i = 0; i < nSize; i++)
        {
            newElements[i] = elements[i];
        }
        
        delete[] elements;
        elements = newElements;
    }
}

template<class T>
void ArrayList<T>::insert(int nIndex, const T& element)
{
    if (nIndex < 0 || nIndex > nSize ) {
        throw illegalIndex("illegalIndex");
    }
    if (nSize == nLength) {
        T* temp = new T[nLength * 2];
        for (int i = 0; i < nLength ; i++)
            temp[i] = elements[i];
        delete [] elements;
        elements = temp;
        nLength *= 2;
    }
    for (int i = nSize-1; i >= nIndex; i--)
        elements[i + 1] = elements[i];
        
    elements[nIndex] = element;
    nSize++;
}

template<class T>
void ArrayList<T>::output(std::ostream& out) const
{
    for (int i = 0; i < nSize; i++) {
        out << elements[i] << ' ';
    }
    out << std::endl;
}

template<class T>
void ArrayList<T>::push_back(const T& elem)
{
    if (nSize == nLength) {
        T* temp = new T[nLength * 2];
        for (int i = 0; i < nLength ; i++)
            temp[i] = elements[i];
        delete [] elements;
        elements = temp;
        nLength *= 2;
    }
    elements[nSize++] = elem;

}

#endif
