#include <iostream>
#include <vector>
using namespace std;

enum Direction{
    LeftUp = 1,
    Up = 2,
    Left = 3,
};
template<class T>
void LCS_length(const vector<T>& X, const vector<T>& Y,vector<vector<int>>& C, vector<vector<Direction>>& B)
{
    int m = X.size()-1;
    int n = Y.size()-1;

    for (int i = 0; i <= m; i++)
        C[i][0] = 0;
    for (int i = 0; i <= n; i++)
        C[0][i] = 0;

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (X[i] == Y[j]){
                C[i][j] = C[i-1][j-1] + 1;
                B[i][j] = LeftUp;
            }
            else{
                if(C[i-1][j] >= C[i][j-1]){
                    C[i][j] = C[i-1][j];
                    B[i][j] = Up;
                }else{
                    C[i][j] = C[i][j-1];
                    B[i][j] = Left;
                }
            }
}

template<class T>
void Print_LCS(const vector<vector<Direction>>& B,const vector<T>& X,int m, int n)
{
    if (m == 0 || n ==0 )
        return;
    if (B[m][n] == LeftUp){
        Print_LCS(B,X,m-1,n-1);
        cout<<X[m]<<" ";
    }
    else if (B[m][n] == Up){
        Print_LCS(B,X,m-1,n);
    }
    else 
        Print_LCS(B,X,m,n-1);

}
int main() {
    vector<string> X = {" ","A","B","C","B","D","A","B"};
    vector<string> Y = {" ","B","D","C","A","B","A"};
    vector<vector<int>> C;
    vector<vector<Direction>> B;
    int m = X.size() - 1;
    int n = Y.size() - 1;
    C.resize(m+1);
    B.resize(m+1);
    for (int i = 0; i <= m; i++)
    {
        C[i].resize(n+1);
        B[i].resize(n+1);
    }
    
    LCS_length(X,Y,C,B);
    Print_LCS(B,X,m,n);
    cout << endl;
    
    return 0;
}