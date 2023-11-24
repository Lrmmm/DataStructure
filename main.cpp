// #define __Test_01__     // List
// #define __Test_02__     // Matrix
// #define __Test_03__     // Stack
// #define __Test_04__     // Queue
// #define __Test_05__     // Dict
// #define __Test_06__     // Hash
// #define __Test_07__     // Trie
// #define __Test_08__     // Tree
// #define __Test_09__     // MaxPriorityQueue
// #define __Test_10__     // SearchTree
#define __Test_11__     // Sort

#include <iostream>
#include "include/include.h"
#include "include/test.h"

using namespace std;
int main() {

#ifdef __Test_01__
    // Test01 ArrayList
    Test01();
#endif
#ifdef __Test_02__
    // Test Matrix
    Test02();
#endif
#ifdef __Test_03__
    Test03()
#endif
#ifdef __Test_04__
    Test04()
#endif

#ifdef __Test_06__
    Test06()
#endif
#ifdef __Test_07__
    Test07()
#endif

#ifdef __Test_08__
    Test08()
#endif
#ifdef __Test_09__
    Test09()
#endif

#ifdef __Test_10__
    Test10();
#endif

#ifdef __Test_11__
    Test11();
#endif
    stack<int> a;
    to_string();
    return 0;
}