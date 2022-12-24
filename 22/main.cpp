#include <bits/stdc++.h>
using namespace std;

const int MAX = 3e3 + 50;

struct node {
    int sum_c, size, par;
    int c, d;
    vector<int> ch;
};
int N, M;
node nodes[MAX];
vector<int> roots, topo_sorted;
int dp_table[MAX][MAX];

node dfs(int root)
{
    nodes[root].sum_c = nodes[root].c;
    nodes[root].size = 1;
    topo_sorted.push_back(root);
    for(auto a : nodes[root].ch) {
        node tmp = dfs(a);
        nodes[root].sum_c += tmp.sum_c;
        nodes[root].size += tmp.size;
    }
    return nodes[root];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    for(int n = 0; n < N; n++) {
        cin >> nodes[n].par;
        if(nodes[n].par == -1) roots.push_back(n);
        else                   nodes[nodes[n].par].ch.push_back(n);
    }
    for(int n = 0; n < N; n++)
        cin >> nodes[n].c >> nodes[n].d;
    for(int x : roots)
        dfs(x);
    for(int n = N - 1; n >=0; n--) {
        int topo = topo_sorted[n];
        for (int m = 1; m <= M; m++) {
            vector<int> three;
            three.push_back(dp_table[n + 1][m]);
            if(m >= nodes[topo].d)
                three.push_back(nodes[topo].sum_c + dp_table[n + nodes[topo].size][m - nodes[topo].d]);
            if(m >= nodes[topo].c)
                three.push_back(nodes[topo].c + dp_table[n + 1][m - nodes[topo].c]);
            dp_table[n][m] = *max_element(three.begin(), three.end());
        }
    }
    // for(int n = 0; n < N; n++) {
    //     for(int m = 0; m < M; m++)
    //         cout << dp_table[n][m] << " ";
    //     cout << "\n";
    // }
    cout << dp_table[0][M] << "\n";
}