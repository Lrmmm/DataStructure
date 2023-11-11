import random
import time
import sys
sys.setrecursionlimit(5000)

def Partition(arry:list, low:int, high:int):
    pivot = arry[high]
    i = low - 1
    j = low
    while j <= high - 1:
        if (arry[j] <= pivot):
            i += 1
            tmp = arry[i]
            arry[i] = arry[j]
            arry[j] = tmp
        j += 1
    tmp = arry[high]
    arry[high] = arry[i + 1]
    arry[i+1] = tmp
    return i+1

def QuickSort(arry:list, low:int, high:int):
    if (low < high):
        pivot =  Partition(arry,low,high)
        QuickSort(arry,low,pivot-1)
        QuickSort(arry,pivot+1,high)

if __name__=='__main__':
    
    arry = []
    iters = 10**7
    for i in range(0,iters):
        arry.append(random.randint(0,2**32-1))
        # arry.append(i)
    
    start_time = time.time()
    QuickSort(arry,0,len(arry)-1)
    end_time = time.time()

    print(end_time - start_time)
    print(arry[0:10])