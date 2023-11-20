/**
 * 动态规划
 *  1. 找出最优解的结构
 *  2. 递归定义最优解
 *  3. 计算最优解的值
 *  4. 构造最优解
*/

#include <iostream>
#include <vector>
#include <array>
#include <time.h>
#include <random>
using namespace std;

namespace matrixchain_dynamic{
// 计算最优解的值
void MatrixChainOrder(const vector<int>& p,vector<vector<int>>& m, vector<vector<int>>& s)
{   

    int n = static_cast<int>(p.size()) - 1;
    
    for (int i = 1; i <= n; i++)
        m[i][i] = 0;

    // 沿着垂直对角线的方向往上计算，先计算l长度为2的，再计算l长度为3的，。。。最后l长度为n，m[n,n]就是我们所求的最优解
    for (int l = 2; l <= n; l++)  // Ai...Aj链长= j-i+1
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;
            m[i][j] = INT32_MAX;
            for (int k = i; k <= j - 1; k++)
            {
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j]){
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

}
}

namespace matrixchain_recurve{
int MatrixChainOrder2(const vector<int>& p,vector<vector<int>>& m, vector<vector<int>>& s, int i, int j)
{
    if (i == j) return 0;
    int min = INT32_MAX;
    int divide = -1;
    for (int k = i; k < j; k++)
    {
        int tmp = (MatrixChainOrder2(p,m,s,i,k) + MatrixChainOrder2(p,m,s,k+1,j) + p[i-1]*p[k]*p[j]);
        if (tmp < min)
        {
            min = tmp;
            divide = k;
        }
    }
    m[i][j] = min;
    s[i][j] = divide;
    return min;
}
}

namespace matrixchain_memoized{

void MatrixChainOrder(vector<int>& p, vector<vector<int>> &m){
    int n = p.size() - 1;
    // 将上三角初始化为INT_MAX
    for(int i = 1; i <= n;i++)
        for (int j = i; j < n; j++)
            m[i][j] = INT32_MAX;
    
    return ;
}

int LookupChain( vector<int> &p,vector<vector<int>>& m, int i, int j){
    if (m[i][j] < INT32_MAX) return m[i][j];

    if (i == j) 
        m[i][j] = 0;
    else {
        for (int k = i; k <= j - 1; k++)
        {
            int q = LookupChain(p,m,i,k) + LookupChain(p,m,k+1,j) + p[i-1]*p[k]*p[j];
            if (q < m[i][j])
                m[i][j] = q;
        }
    }
    return m[i][j];
}

}

void print_optimal_parens(vector<vector<int>>& s, int i, int j)
{
    if (i == j){
        cout << "A" << i;
    }
    else{
        cout <<"(" ;
        print_optimal_parens(s,i,s[i][j]);
        print_optimal_parens(s,s[i][j]+1,j);
        cout <<")";
    }

}

int main() {

    vector<int> p = {30,35,15,5,10,20,25};
    // vector<int> p ;
    // for (int i = 0; i < 10; i++)
    //     p.push_back(rand()%10 + 1);
    
    int n = p.size() - 1;
    vector<vector<int>> m;m.resize(n+1);
    vector<vector<int>> s;s.resize(n+1);
    for (int i = 0; i < n+1; i++)
    {
        m[i].resize(n+1);
        s[i].resize(n+1);
    }
    clock_t start;
    clock_t finish;
    start = clock();
    matrixchain_dynamic::MatrixChainOrder(p,m,s);
    // matrixchain_recurve::MatrixChainOrder2(p,m,s,1,n);
    finish = clock();
    for (int i = 1; i < n+1; i++){
        for (int j = 1; j < n+1; j++)
            cout<< m[i][j] <<"\t";
        cout << endl;
    }
    cout << endl;
    for (int i = 1; i < n+1; i++){
        for (int j = 1; j < n+1; j++)
            cout<< s[i][j] <<"\t";
        cout << endl;
    }
    
    cout << "Time: "<< (double)(finish - start) / CLOCKS_PER_SEC << endl;
    cout << m[1][n] << endl;
    print_optimal_parens(s,1,n);
    cout << endl;
    return 0;
}