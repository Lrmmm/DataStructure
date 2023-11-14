#include <iostream>
#include <vector>
#include <thread>

// 假设这是一个选择排序函数
void SelectSort(std::vector<int>& arr) {
    // 在这里实现选择排序算法
    // ...
    std::cout << "Sorting done." << std::endl;
}

int main() {
    // 创建一个包含一些整数的向量
    std::vector<int> myArr = {4, 2, 7, 1, 9, 5};

    // 创建新线程，执行 SelectSort 函数，并传递向量的引用
    std::thread myThread1(SelectSort, std::ref(myArr));

    // 等待新线程结束
    myThread1.join();

    // 在主线程中继续其他操作
    std::cout << "Main thread continuing." << std::endl;

    return 0;
}