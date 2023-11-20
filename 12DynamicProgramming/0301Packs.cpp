#include <iostream>
#include <vector>
using namespace std;
/**
 * Recursion Approach for 0/1 Knapsack Problem:
 * 非动态规划解决问题(直接利用递归，会有重复调用)
 *  时间复杂度: O(2^n)
 *  空间复杂度: O(n) 最大递归深度
*/
namespace knapsack1{
int KnapSack(const vector<int>& weight, const vector<int>& value, int capacity, int n){
    if (n == 0 || capacity == 0)return 0;

    if (weight[n - 1] > capacity)
        return KnapSack(weight,value,capacity,n-1);
    else 
        return max(
            value[n-1] + KnapSack(weight,value,capacity-weight[n-1],n-1),
            KnapSack(weight,value,capacity,n-1)
        );
}
}

/**
 * Memoization Approach for 0/1 Knapsack Problem
 * 递归+记忆化 = 自顶向下 ， 利用矩阵保存中间结果
 *  时间复杂度: O(n*w)
 *  空间复杂度: O(n*w) + O(n) n次递归
*/
namespace knapsack3{
int KnapSackRec(const vector<int>& weight, const vector<int>& value, int capacity, int index,vector<vector<int>>& dp)
{
    if (index < 0) return 0;

    if (dp[index][capacity] != -1)
        return dp[index][capacity];
    
    if (weight[index] > capacity){
        dp[index][capacity] = KnapSackRec(weight,value,capacity,index-1,dp);
        return dp[index][capacity];
    }
    else {
        dp[index][capacity] = max(
                                    value[index] + KnapSackRec(weight,value,capacity-weight[index],index-1,dp),
                                    KnapSackRec(weight,value,capacity,index - 1,dp)
                                );
        return dp[index][capacity];
    }
}
int KnapSack(const vector<int>& weight, const vector<int>& value, int capacity){
    
    int n = weight.size();
    vector<vector<int>> dp(n,vector<int>(capacity+1));

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= capacity; j++)
            dp[i][j] = -1;
    return KnapSackRec(weight,value,capacity,n-1,dp);
}

}

/**
 * Bottom-up Approach for 0/1 Knapsack Problem:
 *  不利用递归，自底向上的动态规划
 *   时间复杂度: O(n*w)
 *   空间复杂度: O(n*w)
*/
namespace knapsack4{
int KnapSack(const vector<int>& wt, const vector<int>& val,int capacity){

    int n = wt.size();
    vector<vector<int>> dp(n+1,vector<int>(capacity+1));
    
    for (int i = 0; i <= n; i++)    
        for (int j = 0; j <= capacity; j++)
        {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if(wt[i -1] <= capacity)
                dp[i][j] = max(val[i-1] + dp[i-1][j-wt[i-1]] , dp[i-1][j]);
            else 
                dp[i][j] = dp[i-1][j];
        }

    return dp[n][capacity];
}
}


/**
 * Space optimized Approach for 0/1 Knapsack Problem using Dynamic Programming
 * 不利用递归，自底向上的动态规划, 优化dp数组
 *  时间复杂度: O(n*w)
 *  空间复杂度: O(w)
*/
namespace knapsack5{

int KnapSack(const vector<int>& wt, const vector<int>& val,int ca)
{
    int n = wt.size();
    vector<int> dp(ca+1);

    for (int i = 1; i <= n; i++)
        for (int j = ca; j >= 0; j--)
            if(wt[i-1] <= j)
                dp[j] = max(dp[j],dp[j-wt[i-1]]+val[i-1]);
        
    return dp[ca];
}

}
int main() {
    vector<int> w = {10,20,30};
    vector<int> v = {60,100,120};
    int capacity = 50 ;
    // cout << knapsack::Knapsack(w,v,capacity) << endl;
    // cout << knapsack1::KnapSack(w,v,capacity,w.size()) << endl;
    // cout << knapsack2::KnapSack(w,v,capacity) << endl;
    // cout << knapsack3::KnapSack(w,v,capacity) << endl;
    cout << knapsack4::KnapSack(w,v,capacity) << endl;
    return 0;
}