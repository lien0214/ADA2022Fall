#include <bits/stdc++.h>
#include "ypglpk.hpp"
using namespace std;
const int BIG_NUM = 5000;
const int PLUS = 1, MINUS = -1;
const int NONSENCE = 3;
struct edge {
    int from;
    int to;
    int w;
};

int N, M;

int main()
{
    cin >> N >> M;
    vector<int> vartype(M + N);
    vector<vector<double>> A_matrix((M + 3 * N), vector<double>(M + N));
    vector<double> c_matrix(M + N);
    vector<double> b_matrix(M + 3 * N);
    vector<double> tmp(M + N);
    edge E[M];
    for(int i = 0; i < N; vartype[i++] = GLP_IV)
        c_matrix[i] = 0;

    for(int i = 0; i < M; i++)
    {
        cin >> E[i].from >> E[i].to >> E[i].w;
        c_matrix[N + i] = E[i].w;
        vartype[N + i] = GLP_BV;
    }
    for(int h = 0; h < M; h++) {
        tmp[h] = 0;
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N + M; j++) {
            if (j >= N) {
                A_matrix[i][j] = (i == j - N) ? BIG_NUM : 0;
                continue;
            }
            A_matrix[i][j] = 0;
            if (j + 1 == E[i].from)
                A_matrix[i][j] = 1;
            if (j + 1 == E[i].to)
                A_matrix[i][j] = -1;   
        }
        b_matrix[i] = BIG_NUM - 1;
    }
    for(int h = 0; h < M; h++) {
        tmp[h] = tmp[h + 1] * tmp[h + 2];
    }
    for (int i = M; i < M + N; i++) {
        for(int j = 0; j < N + M; j++){
            if(j < N) {
                A_matrix[i][j] = A_matrix[i + N][j] = 0;
                continue;
            }
            if (i == M + N - 1) {
                if (E[j - N].from == i - M + 1)
                    A_matrix[i][j] = A_matrix[i + N][j] = BIG_NUM;
                else if (E[j - N].to == i - M + 1) {
                    A_matrix[i][j] = -1;
                    A_matrix[i + N][j] = 1;
                }
                else A_matrix[i][j] = A_matrix[i + N][j] = 0;
            }
            else if (i == M)
            {
                if (E[j - N].from == i - M + 1)
                {
                    A_matrix[i][j] = 1;
                    A_matrix[i + N][j] = -1;
                }
                else if (E[j - N].to == i - M + 1)
                    A_matrix[i][j] = A_matrix[i + N][j] = BIG_NUM;
                else
                    A_matrix[i][j] = A_matrix[i + N][j] = 0;
            }
            else
            {
                A_matrix[i][j] = (E[j - N].from == i - M + 1) ? 1 : -1;
                A_matrix[i + N][j] = (E[j - N].to == i - M + 1) ? 1 : -1;
                if(E[j - N].from != i - M + 1 && E[j - N].to != i - M + 1)
                    A_matrix[i][j] = A_matrix[i + N][j] = 0;
            }
        }

        b_matrix[i] = (i == M + N - 1) ? -1 : 1;
        b_matrix[i + N] = (i == M) ? -1 : 1;
        if(i != M + N - 1 && i != M)
            b_matrix[i] = b_matrix[i + N] = 0;
    }

    for (int i = M + 2 * N; i < M + 3 * N; i++) {
        for (int j = 0; j < N + M; j++) {
            if(j >= N && E[j - N].from == i - M - 2 * N + 1) A_matrix[i][j] = 1;
            else                                             A_matrix[i][j] = 0;
        }
        if(i == M + 3 * N - 1) b_matrix[i] = false;
        else                   b_matrix[i] = true;
    }

    pair<double, vector<double>> output = ypglpk::mixed_integer_linear_programming(A_matrix, b_matrix, c_matrix, vartype);

    if (output.second.size() == 0) {
        cout << "-1";
        return 0;
    }
    cout << (int)output.first << "\n";
    for (int i = 0; i < M; i++)
        cout << output.second[N + i];

    return 0;
}