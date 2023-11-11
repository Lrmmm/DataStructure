#include "../include/include.h"
void Test03()
{
    // Test DeriveArrayStack
    DeriveArrayStack<int> myStack1;
    myStack1.push(1);
    myStack1.push(2);
    myStack1.pop();
    myStack1.push(3);
    // myStack1.pop();
    cout << myStack1 << endl;

    // Test LinkStack
    LinkStack<int> myStack2;
    myStack2.push(1);
    myStack2.push(2);
    myStack2.pop();
    myStack2.push(9);
    myStack2.push(8);
    cout << myStack2 << endl;
}