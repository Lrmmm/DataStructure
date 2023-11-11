#include "../include/include.h"
void Test04()
{
    // Test ArrayQueue
    ArrayQueue<int> myQueue1;
    myQueue1.push(1);
    myQueue1.push(2);
    myQueue1.push(3);
    myQueue1.push(4);
    myQueue1.pop();
    cout << myQueue1 << endl;

    // Test LinkedQueue
    LinkedQueue<int> myQueue2;
    myQueue2.push(2);
    myQueue2.push(3);
    myQueue2.push(4);
    myQueue2.push(5);
    myQueue2.pop();
    cout << myQueue2 << endl;
}