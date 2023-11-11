#include<iostream>
#include"Tree234.hpp"
using namespace std;
using namespace data_structures;

/** @brief simple test to insert a given array and delete some item, and print
 * the tree*/
static void test1() {
    std::array<int16_t, 13> arr = {3, 1, 5, 4, 2, 9, 10, 8, 7, 6, 16, 13, 14};
    data_structures::tree_234::Tree234 tree;

    for (auto i : arr) {
        tree.Insert(i);
    }

    // tree.Remove(10);
    tree.Remove(5);
    tree.Print();
}

/**
 * @brief simple test to insert continuous number of range [0, n), and print
 * the tree
 * @param n upper bound of the range number to insert
 */
static void test2(int64_t n) {
    data_structures::tree_234::Tree234 tree;

    for (int64_t i = 0; i < n; i++) {
        tree.Insert(i);
    }

    tree.Traverse();
    tree.Print((std::to_string(n) + ".dot").c_str());
}

/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        test1();  // execute 1st test
    } else {
        test2(std::stoi(argv[1]));  // execute 2nd test
    }

    return 0;
}