#include <iostream>
#include <vector>
using namespace std;


void DynamicActivitySelector(const vector<int>& s, const vector<int>&f, vector<vector<int>>& C, vector<vector<int>>& A)
{
    int n = s.size() - 2;
    for (int i = 0; i <= n; i++)
    {
        C[i][i] = 0;
        C[i][i+1] = 0;
    }
    C[n+1][n+1]= 0;

    for (int len = 2; len <= n+1; len++)
        for (int i = 0; i <= n - len + 1; i++)
        {
            int j = i + len;
            C[i][j] = 0;
            int k = j - 1;
            while (f[i] < f[k]){
                if (f[i] <= s[k] && f[k] <= s[j] && C[i][k] + C[k][j] + 1 > C[i][j]){
                    C[i][j] = C[i][k] + C[k][j] + 1 ;
                    A[i][j] = k;
                }
                k = k - 1;
            }
        }
}

void RecursiveActivitySelector(const vector<int>& s, const vector<int>&f, int i,int j,vector<int>& solu)
{
    int m  = i + 1;
    while (m < j && s[m] < f[i])
        m = m + 1;
    if (m < j){
        solu.push_back(m);
        RecursiveActivitySelector(s,f,m,j,solu);
    }
    else 
        return;
    
}

vector<int> GreedyActivitySelector(const vector<int>& s, const vector<int>&f)
{
    vector<int> solu;
    int n = s.size() - 2;
    solu.push_back(1);
    int i = 1;
    for (int m = 2; m <= n; m++)
    {
        if (f[i] < s[m]){
            solu.push_back(m);
            i = m;
        }
    }
    return solu;

}

void PrintResult(vector<vector<int>>& C,vector<vector<int>>& A,int i, int j)
{
    if (C[i][j] > 0){
        PrintResult(C,A,i,A[i][j]);
        cout << "A" << A[i][j] << " ";
        PrintResult(C,A,A[i][j]+1,j);
    }
}

int main() {
    vector<int> s = {0,1,3,0,5,3,5,6,8,8,2,12,99};
    vector<int> f = {0,4,5,6,7,9,9,10,11,12,14,16,99};
    vector<vector<int>> C;
    vector<vector<int>> A;
    vector<int> solu;
    int n = s.size() - 2;
    C.resize(n+2);
    A.resize(n+2);
    for (int i = 0; i <= n+1; i++)
    {
        C[i].resize(n+2);
        A[i].resize(n+2);
    }
    
    // DynamicActivitySelector(s,f,C,A);
    // PrintResult(C,A,0,n+1);
    // RecursiveActivitySelector(s,f,0,n+1,solu);
    solu = GreedyActivitySelector(s,f);
    for (int i = 0; i < solu.size(); i++)
        cout << solu[i] <<" ";
    
    return 0;
}