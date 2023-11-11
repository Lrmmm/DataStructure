#include "../include/include.h"
void Test02(){
    Matrix<int> myMatrix1(2,3);
    myMatrix1(1,1) = 1;
    myMatrix1(1,2) = 2;
    myMatrix1(1,3) = 3;
    myMatrix1(2,1) = 4;
    myMatrix1(2,2) = 5;
    myMatrix1(2,3) = 6;

    Matrix<int> myMatrix2(2,3);
    myMatrix2(1,1) = 1;
    myMatrix2(1,2) = 1;
    myMatrix2(1,3) = 1;
    myMatrix2(2,1) = 1;
    myMatrix2(2,2) = 1;
    myMatrix2(2,3) = 1;
    cout << myMatrix1 << endl;
    cout << myMatrix1 + myMatrix2 << endl;
}