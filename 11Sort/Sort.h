#pragma once
#include<iostream>
#include<cstdlib>
#include "Util.h"
#include <climits>
#include <random>
#include <algorithm>
using namespace std;

/**
 * 1.冒泡排序
 *  
 *  稳定的排序
 *  平均：O(n^2)
 *  最好：O(1)   有序的状态下直接break
 *  最差：O(n^2)
 * 
*/
template<class List>
void BubbleSort(List& list)
{
    bool bSwapped;
    for (int i = 0; i < (int)list.size() - 1; i++){
        bSwapped = false;
        for (int j = 0; j < (int)list.size() - 1 - i; j++)
            if (list[j] > list[j+1]){
                _swap(list[j],list[j+1]);
                bSwapped = true;
            }
        if (!bSwapped)  break;
    }
}

/**
 * 2.选择排序
*/
template<class List>
void SelectSort(List& list)
{
    for (int i = 0; i < (int)list.size() - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < (int)list.size(); j++)
            if (list[j] < list[min_idx])
                min_idx = j;
        if ( min_idx != i ){
            _swap(list[min_idx],list[i]);
        }
    }
}

/**
 * 3.插入排序 -利用交换
*/
template<class List>
void InsertSort_swap(List& list)
{
    for (int i = 1; i < (int)list.size(); i++)
        for (int j = i; j > 0 && list[j] < list[j - 1]; j--)
            _swap(list[j],list[j - 1]);
}

/**
 * 3.插入排序 -利用移位
*/
template<class List>
void InsertSort_move(List& list)
{
    for (int i = 1; i < (int)list.size(); i++)
    {
        auto tmp = list[i];
        int j;
        for (j = i; j > 0 && list[j-1] > tmp; j--)
            list[j] = list[j-1];
        list[j] = tmp;
    }
}  

/**
 * 3.插入排序 -折半插入
*/
template<class List>
void InsertSort_bin(List& list)
{
    for (int i = 1; i < (int)list.size(); i++)
    {
        auto tmp = list[i];
        int index = BinarySearchIndex(list,0,i-1,tmp);
        for (int j = i - 1; j >= index; j--)
            list[j+1] = list[j];
        list[index] = tmp;
    }
} 


/**
 * 4.希尔排序
*/
template<class List>
void ShellSort(List& list)
{
    int step, h;
    int N = (int)(list.size());
    for (h = 1; h <= N/9; h = 3*h + 1);

    for (;h > 0; h = h / 3)
    {
        for (step = h ; step < N; step++)
        {
            int i;
            auto tmp = list[step];
            for ( i = step - h; i >= 0 && tmp < list[i]; i = i - h)
                    list[i + h] = list[i];
            list[i + h] = tmp;            
        }
    }
}

/**
 * 5.快速排序-非随机版本
*/
namespace quicksort_nrandom{
    template<class List>
    int _partition(List& list, int low, int high)
    {
        /**
         * [low..j-1]为已经划分好的区间，初始时为空[low..low-1]
         *      [low..j-1] -> 小于区间[low..i] + 大于区间[i+1..j-1]
         *       i : 始终指向小于区间的最后一个元素，初始时为越界值low-1
         *       j : 始终指向第一个待划分的元素，也即是已经划分好区间右边的第一个元素
         *           最终，j指向high，划分结束，交换list[high]和list[i+1]
         * */ 
        auto pivot = list[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++)
        {
            if (list[j] <= pivot){
                i++;
                _swap(list[i],list[j]);
            }
        }
        _swap(list[i+1],list[high]); 
        return i + 1;
    }

    template<class List>
    void _quickSort(List& list, int low, int high)
    {
        if (low < high) {
            int pivot = _partition(list,low,high);
            _quickSort(list,low, pivot-1);
            _quickSort(list,pivot+1,high);
        }
    }
    template<class List>
    void QuickSort(List& list){_quickSort(list,0,list.size()-1);}
}

/**
 * 5.快读排序-随机版本
*/
namespace quicksort_random{
    template<class List>
    int _partition(List& list, int low, int high)
    {
        /**
         * [low..j-1]为已经划分好的区间，初始时为空[low..low-1]
         *      [low..j-1] -> 小于区间[low..i] + 大于区间[i+1..j-1]
         *       i : 始终指向小于区间的最后一个元素，初始时为越界值low-1
         *       j : 始终指向第一个待划分的元素，也即是已经划分好区间右边的第一个元素
         *           最终，j指向high，划分结束，交换list[high]和list[i+1]
         * */ 
        int random = rand() % (high - low + 1) + low;
        _swap(list[high],list[random]);
        auto pivot = list[high];
        int i = low - 1;
        for (int j = low; j <= high - 1; j++)
        {
            if (list[j] < pivot){
                i++;
                _swap(list[i],list[j]);
            }
            else if (list[j] == pivot && rand()%2 == 0){
                i++;
                _swap(list[i],list[j]);
            }
        }
        _swap(list[i+1],list[high]); 
        return i + 1;
    }

    template<class List>
    void _quickSort(List& list, int low, int high)
    {
        if (low < high) {
            int pivot = _partition(list,low,high);
            _quickSort(list,low, pivot-1);
            _quickSort(list,pivot+1,high);
        }
    }
    template<class List>
    void QuickSort(List& list){_quickSort(list,0,list.size()-1);}
}

/**
 * 6.堆排序
*/
namespace heapsort{

int parent(int i){return i > 0 ?(i - 1) / 2 : -1; }
int left(int i){return i*2 + 1;}
int right(int i){return i*2 + 2;}

template<class List>
void heapify(List& list,int curr,int size)
{
    auto currElement = list[curr];
    int child = left(curr);
    while (child <= size - 1)
    {
        if (child < size - 1 && list[child] < list[child+1])
            child++;
        if(currElement > list[child])
            break;
        list[parent(child)] = list[child];
        child = left(child);
    }
    list[parent(child)] = currElement;
}

/**
 * s
*/
template<class List>
void HeapSort(List& list)
{
    // 1.建立大根堆
    int size = list.size();
    for (int curr = size / 2 -1;curr >= 0; curr-- )
        heapify(list,curr,size);

    // 2.每次把大根堆的一个元素拿出来和最后一个元素交换
    while(size > 1)
    {
        _swap(list[0],list[size - 1]);
        size--;
        heapify(list,0,size);
    }
}
}

/**
 * 7.归并排序
*/
namespace mergesort{

template<class List>
void _merge(List& list, int left, int mid, int right)
{
    List temp(right - left + 1);
    int i = left;
    int j = mid + 1;
    int k = 0;

    while( i <= mid && j <= right){
        if(list[i] < list[j])
            temp[k++] = list[i++];
        else 
            temp[k++] = list[j++];
    }

    while (i <= mid)
        temp[k++] = list[i++];
    while (j <= right)
        temp[k++] = list[j++];
    
    for (int m = left,n=0; m<=right;m++,n++)
        list[m] = temp[n];
}
template<class List>
void _mergersort(List& list, int left,int right)
{
    if (left == right)
        return;
    int mid = (left+right)/2;
    _mergersort(list,left,mid);
    _mergersort(list,mid+1,right);
    _merge(list,left,mid,right);

}
template<class List>
void MergeSort(List& list)
{
    _mergersort(list,0,list.size()-1);
}

}

/**
 * 8.计数排序
 * 适用范围：一定范围内的"整数"
*/
void CountSort(vector<int>& list,int nMax, int nMin)
{
    int size = nMax-nMin+1;
    vector<int> countList(size,0);
    for (int i = 0; i < (int)list.size(); i++)
        countList[list[i]-nMin]++;
    for (int i = 1; i < size; i++)
        countList[i] += countList[i-1];

    vector<int> outputList((int)list.size());
    for (int i = (int)list.size() - 1; i >= 0; i--)
    {
        outputList[countList[list[i]-nMin] - 1] = list[i];
        countList[list[i]-nMin]--;
    }
    
    for (int i = 0; i < (int)list.size(); i++)
        list[i] = outputList[i];
}



/**
 * 9.基数排序
 * 适用范围:整数、字符串
 * 
*/
namespace radixsort{

int getMax(const vector<int>& list)
{
    int max = list[0];
    for (int i = 1; i < (int)list.size(); i++)
        if(list[i] > max)
            max = list[i];
    return max;
}
void countsortForRadix(vector<int>& list,int exp)
{
    vector<int> outList(list.size());
    vector<int> countList(10,0);
    for (int i = 0; i < (int)list.size(); i++)
        countList[(list[i]/exp)%10]++;
    for (int i = 1; i < 10; i++)
        countList[i] += countList[i-1];
    for (int i = (int)list.size() - 1; i >=0; i--)
    {
        outList[countList[(list[i]/exp)%10]-1] = list[i];
        countList[(list[i]/exp)%10]--;
    }
    for(int i = 0; i < (int)list.size();i++)
        list[i] = outList[i];
    
}
void RadixSort(vector<int>& list)
{
    int nMax = getMax(list);
    for (int expr = 1; nMax / expr > 0; expr*=10)
        countsortForRadix(list,expr);
}   

}

/**
 * 10.桶排序
 * 是一种空间换时间的排序方法
 * 适用场景：假设数据在[min,max]之间均匀分布，知道上界max和下界min，一般[0,1]
*/
namespace bucketsort{
/**
 * 10.桶排序-[0,1]范围
 * 是一种空间换时间的排序方法
 * 适用场景：假设数据在[min,max]之间均匀分布，知道上界max和下界min，一般[0,1]
*/
void BucketSort_01(vector<float> list)
{
    int size = list.size();
    vector<float> bucket[size];
    for (int i = 0; i < size; i++){
        int bi = size*list[i];
        bucket[bi].push_back(list[i]);
    }

    for(int i=0; i<size;i++)
        sort(bucket[i].begin(),bucket[i].end());
    int idx = 0;
    for (int i = 0; i < size; i++)
        for(int j = 0; j <(int)bucket[i].size();j++)
            list[idx++] = bucket[i][j];
}

int getBucketIndex(int k,int nMin,int nMax,int value)
{
    double percentage = (double)(value-nMin)/(nMax+1-nMin+1);
    return (int)(percentage * k);
}
void BucketSort_Int(vector<int>& list,int k,int nMin,int nMax)
{
    int size = list.size();
    vector<int> buckets[k];
    for (int i = 0; i < size; i++)
        buckets[getBucketIndex(k,nMin,nMax,list[i])].push_back(list[i]);
    
    for (int i = 0; i < k; i++)
        // InsertSort_swap(buckets[i]);
        quicksort_nrandom::QuickSort(buckets[i]);
    
    int idx =  0;
    for (int i = 0; i < k; i++)
        for (int j = 0; j < (int)buckets[i].size(); j++)
            list[idx++] = buckets[i][j];
}
}

