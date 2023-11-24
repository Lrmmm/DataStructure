#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <time.h>
#include <thread>
#include <unordered_set>
using namespace std;

namespace queen_backtrace{

bool isSafe(const vector<int>& res, int i, int j)
{
    for (int index = i-1; index >= 0; index--)
        if (res[index] == j || index - res[index] == i - j || index + res[index] == i + j)
            return false;
    
    return true;
    
}

vector<int> Queen(int n)
{
    vector<int> res(n,-1);

    int i = 0;
    int j = 0;
    while (i < n)
    {
        bool isFind = false;
        for (; j < n ; j++)
            if(isSafe(res,i,j)){
                isFind = true;
                break;
            }
        if (isFind){
            res[i] = j;
            j = 0;
            i++;
        }
        else{
            i--;
            j = res[i]+1;
        }
    }
    
    return res;
    
}
}

namespace queen_lv{
bool isSafe(const vector<int>& res, int i, int j)
{
    for (int index = i-1; index >= 0; index--)
        if (res[index] == j || index - res[index] == i - j || index + res[index] == i + j)
            return false;
    
    return true;
    
}

bool LV(vector<int>& res,int n){
    int i = 0;
    int nb = 0;
    do {
        nb = 0;
        int k;
        for (int j = 0; j < n; j++)
        {
            if(isSafe(res,i,j)){
                nb++;
                if (rand()%nb == 0)
                    k = j;
            }
        }

        if (nb > 0) {
            res[i] = k;
            i++;

        }
    }while(nb != 0 && i != n);
    return nb > 0;
}
vector<int> Queen(int n){
    vector<int> res(n,-1);

    while (!LV(res,n)){}

    return res;
}
}

namespace queen_lblv{

bool isSafe(const vector<int>& res, int i, int j)
{
    for (int index = i-1; index >= 0; index--)
        if (res[index] == j || index - res[index] == i - j || index + res[index] == i + j)
            return false;
    
    return true;
    
}

bool BackTrace(vector<int>& res,int n, int k){
    int i = k;
    int j = 0;
    while (i < n)
    {
        bool isFind = false;
        for ( ; j < n; j++)
            if(isSafe(res,i,j)){
                isFind = true;
                break;
            }
        if (isFind){
            res[i] = j;
            j = 0;
            i++;
        }
        else {
            i--;
            if (i < k) return false;
            j = res[i]+1;
        }
        if (i == k && j == n) return false;
    }
    return true;
}

bool LV(vector<int>& res,int n,int k){
    int i = 0;
    int nb = 0;
    do {
        nb = 0;
        int k;
        for (int j = 0; j < n; j++)
        {
            if(isSafe(res,i,j)){
                nb++;
                if (rand()%nb == 0)
                    k = j;
            }
        }

        if (nb > 0) {
            res[i] = k;
            i++;

        }
    }while(nb != 0 && i != k);
    if (nb > 0){
        return BackTrace(res,n,k);
    }
    else 
        return false;
}

vector<int> Queen(int n, int k){
    vector<int> res(n,-1);

    while (!LV(res,n,k)){}

    return res;
}
}


int main() {
    int n = 32;
    vector<int> res;
    // auto res = queen_recall::Queen(n);
    srand(time(0));

    clock_t start;
    clock_t finish;
    start = clock();
    res = queen_backtrace::Queen(n);
    // res = queen_lv::Queen(n);
    // res = queen_lblv::Queen(n,n/2);
    finish = clock();
    for (int i = 0; i < n; i++)
        cout << res[i] << endl;
    cout << endl;
    cout << "Time: "<< (double)(finish - start) / CLOCKS_PER_SEC << endl;
    
    return 0;
}