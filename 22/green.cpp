#include <bits/stdc++.h>
using namespace std;
#define NUM 301
typedef struct p {
    int c, d, sum_c, size;
} p;
int N, M, idx[NUM], prt[NUM], cnt = 0;
vector<int> pts[NUM], roots;
p grn[NUM];
p dfs(int cur){
    grn[cur].sum_c = grn[cur].c, grn[cur].size = 1;
    idx[cnt] = cur, cnt++;
    int len = pts[cur].size();
    for(int i = 0; i < len; i++){
        p tmp = dfs(pts[cur][i]);
        grn[cur].sum_c += tmp.sum_c, grn[cur].size += tmp.size;
    }
    return grn[cur];
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        cin >> prt[i];
        if(prt[i] == -1)
            roots.push_back(i);
        else pts[prt[i]].push_back(i);
    }
    for(int i = 0; i < N; i++)
        cin >> grn[i].c >> grn[i].d;
    int sz = roots.size(), cnt = 0; 
    for(int i = 0; i < sz; i++)
        dfs(roots[i]);
    int table[NUM][NUM];
    for(int i = 0; i < NUM; i++)
        table[N][i] = 0;
    for(int i = N-1; i >= 0; i--){
        for(int j = 1; j <= M; j++){
            int a = 0, b = 0;
            table[i][j] = table[i + 1][j];
            if(j >= grn[idx[i]].d)
                a = grn[idx[i]].sum_c + table[i + grn[idx[i]].size][j - grn[idx[i]].d];
            if(j >= grn[idx[i]].c)
                b = grn[idx[i]].c + table[i + 1][j - grn[idx[i]].c];
            table[i][j] = max(max(a, b), table[i][j]);
        }
    }
    for(int n = 0; n < N; n++) {
        for(int m = 0; m < M; m++)
            cout << table[n][m] << " "
        cout << "\n";
    }
    cout << table[0][M] << "\n";
}