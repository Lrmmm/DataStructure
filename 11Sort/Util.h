#pragma once
#include<iostream>
using namespace std;
template<class List>
void printList(const List& list){
    for (auto item : list)
        cout << item <<" ";
    cout << endl;
}

template<class T>
void _swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template<class List, class T>
int BinarySearch(const List& list,int l, int r, T key)
{
    int left = l;
    int right = r;
    while (left <= right)
    {
        int middle =(left + right) / 2;
        if (list[middle] == key)
            return middle;
        if (key > list[middle])
            left = middle + 1;
        else
            right = middle - 1;
    }
    return -1;
}

template<class List, class T>
int BinarySearchIndex(const List& list,int l, int r, T key)
{
    int left = l;
    int right = r;
    while (left <= right)
    {
        int middle =(left + right) / 2;
        if (list[middle] == key)
            return middle + 1;
        if (key > list[middle])
            left = middle + 1;
        else
            right = middle - 1;
    }
    return left;
}