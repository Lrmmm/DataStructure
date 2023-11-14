#pragma once
#include "../11Sort/Sort.h"
#include <iostream>
#include<vector>
#include<cstdlib>
#include <time.h>
#include <algorithm>
#include "../09MaxPriorityQueue/MaxPriorityQueue.h"
#include "../09MaxPriorityQueue/MaxHeap.hpp"
#include <thread>
using namespace std;
#define MIL 10000
// void SelectSort(std::vector<int>& arr) {
//     // 在这里实现选择排序算法
//     // ...
//     std::cout << "Sorting done." << std::endl;
// }
void Test11()
{
    clock_t start,finish;
    
    vector<int> myArr;
    vector<int> myArr2;

    for (int i = 0; i < 10000*MIL; i++)
        myArr.push_back(rand());
    for (int i = 0; i < 10000*MIL; i++)
        myArr2.push_back(rand());
        // myArr.push_back(i);
    // for (int i = 0; i < (25000*MIL); i++)
    //     myArr2.push_back(rand());
    int nMin = INT_MAX;
    int nMax = 0;
    int size = myArr.size();
    for (int i = 0; i < size; i++)
    {
        nMin = myArr[i] < nMin ?  myArr[i] : nMin;
        nMax = myArr[i] > nMax ?  myArr[i] : nMax;
    }
    
    cout<<"Max:"<<nMax<<endl;
    cout<<"Min:"<<nMin<<endl;
    cout<<"Size:"<<size<<endl;
    cout << RAND_MAX << endl;
    start=clock();
    // SelectSort(myArr);
    // BubbleSort(myArr);
    // InsertSort_swap(myArr);
    // InsertSort_move(myArr);
    // InsertSort_bin(myArr);
    // ShellSort(myArr);
    // quicksort_nrandom::QuickSort(myArr);
    // quicksort_random::QuickSort(myArr);
    // sort(myArr.begin(),myArr.end());
    // heapsort::HeapSort(myArr);
    // mergesort::MergeSort(myArr);
    // CountSort(myArr,nMin,nMax);
    // radixsort::RadixSort(myArr);
    // BucketSort_Int(myArr,size/1600,nMin,nMax);
    std::thread myThread1(quicksort_random::QuickSort<vector<int>>,std::ref(myArr));
    std::thread myThread2(quicksort_nrandom::QuickSort<vector<int>>,std::ref(myArr2));
    myThread1.join();
    myThread2.join();
    finish=clock();
    cout << "Time: " <<(double)(finish - start) / CLOCKS_PER_SEC << endl;
    cout << "Size: " <<myArr.size() << endl;
    for (int i = 0; i < 10; i++)
        cout << myArr[i] <<" ";
    cout << endl;
    
    for (int i = 0; i < 10 && i < (int)myArr.size()-1; i++)
        cout << myArr[myArr.size()-i-1] <<" ";

    cout << endl;

    
    // BubbleSort(myArr);
    // SelectSort(myArr);
    // InsertSort_bin(myArr);
    // printList(myArr);
}

