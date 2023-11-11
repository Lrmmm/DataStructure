#include "../include/include.h"
void Test09()
{
    class Compare{
    public:
        bool operator()(int a, int b)
        {
            return a >b ? true :false;
        }
    };
    MaxHeap<int,Compare> myHeap(20);
    myHeap.push(6);
    myHeap.push(10);
    myHeap.push(5);
    myHeap.push(4);
    myHeap.push(3);
    myHeap.push(8);
    cout << myHeap << endl;

    while (!myHeap.empty())
    {
        cout << myHeap.top() << endl;
        myHeap.pop();
    }
    int* pArray = new int[6];
    pArray[0] = 6;pArray[1] = 10;pArray[2] = 5;pArray[3] = 4;pArray[4] = 3;pArray[5] = 8;
    myHeap.initialize(pArray,6);
    cout << myHeap << endl;
}