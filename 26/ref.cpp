羅煜翔
#include "ypglpk.hpp"
#include <bits/stdc++.h>
using namespace std;

struct edge {
    int start, end, cost;
};

int main(){
    int n, m;
    cin >> n >> m;
    vector<vector<double>> A((m + 3*n), vector<double>(m + n));
    vector<double> b(m + 3*n), c(m + n);
    vector<int> vartype(m + n);
    edge E[m];
    for(int i = 0; i < n; i++)
        c[i] = 0, vartype[i] = GLP_IV;
    for(int i = 0; i < m; i++){
        cin >> E[i].start >> E[i].end >> E[i].cost;
        c[n + i] = E[i].cost, vartype[n + i] = GLP_BV;
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n + m; j++){
            if(j < n){
                if(E[i].start == j + 1) 	A[i][j] = 1;
                else if(E[i].end == j + 1) 	A[i][j] = -1;
                else 						A[i][j] = 0;
            } else {
                if(i == j - n) 	A[i][j] = 2000;
                else 			A[i][j] = 0;
            }
        }
        b[i] = 1999;
    }
    for(int i = m; i < m + n; i++){
        for(int j = 0; j < n + m; j++){
            if(j < n) A[i][j] = A[i + n][j] = 0;
            else {
                if(i == m){
                    if(E[j - n].start == i - m + 1)
                        A[i][j] = 1, A[i + n][j] = -1;
                    else if(E[j - n].end == i - m + 1)
                        A[i][j] = A[i + n][j] = 2000;
                    else 
                        A[i][j] = A[i + n][j] = 0;
                }
                else if(i == m + n - 1){
                    if(E[j - n].start == i - m + 1)
                        A[i][j] = A[i + n][j] = 2000;
                    else if(E[j - n].end == i - m + 1)
                        A[i][j] = -1, A[i + n][j] = 1;
                    else 
                        A[i][j] = A[i + n][j] = 0;
                }
                else {
                    if(E[j - n].start == i - m + 1)
                        A[i][j] = 1, A[i + n][j] = -1;
                    else if(E[j - n].end == i - m + 1)
                        A[i][j] = -1, A[i + n][j] = 1;
                    else 
                        A[i][j] = A[i + n][j] = 0;
                }
            }
        }
        if(i == m) 				b[i] = 1, b[i + n] = -1;
        else if(i == m + n - 1) b[i] = -1, b[i + n] = 1;
        else 					b[i] = b[i + n] = 0;
    }
    for(int i = m + 2*n; i < m + 3*n; i++){
        for(int j = 0; j < n + m; j++){
            if(j < n) A[i][j] = 0;
            else A[i][j] = (E[j - n].start == i - m - 2*n + 1);
        }
        b[i] = (i != m + 3 * n - 1);
    }
    pair<double, vector<double>> ret = ypglpk::mixed_integer_linear_programming(A, b, c, vartype);
    if(ret.second.size() == 0) cout << "-1";
    else {
        cout << (int)ret.first << "\n";
        for(int i = 0; i < m; i++)
            cout << ret.second[n + i];
    }
}