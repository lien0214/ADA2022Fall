#include <bits/stdc++.h>
using namespace std;
#define MAXN (1 << 18)
typedef long long ll;
const int white = 0, gray = 1, black = 2;
const int normal = 0, transpose = 1;
struct node {
    vector<int> to;
    vector<int> from;
    int color;
    int pre;
};
node v[MAXN];
int N, M;
vector<int> f_seq = {0};
ll cnt;

ll DFS_visit(int u, int way) {
    ll ret = 1;
    v[u].color = gray;
    if(way == normal) {
        for(int t = 0, T = v[u].to.size(); t < T; t++) {
            if(v[v[u].to[t]].color == white)
                DFS_visit(v[u].to[t], way);
        }
    }
    else if(way == transpose) {
        for(int f = 0, F = v[u].from.size(); f < F; f++) {
            if(v[v[u].from[f]].color == white) {
                v[f].pre = v[u].pre;
                ret += DFS_visit(v[u].from[f], way);
            }
        }
    }
    v[u].color = black;
    f_seq.push_back(u);
    return ret;
}

ll DFS(int way)
{
    int time = 0;
    ll ret = 0;
    for(int n = 1; n <= N; n++) {
        v[n].pre = 0;
        v[n].color = white;
    }
    if(way == normal) {
        for(int n = 1; n <= N; n++) {
            if(v[n].color == white) {
                v[n].pre = n;
                DFS_visit(n, way);
            } 
        }
    }
    else if(way == transpose) {
        for(int n = N; n > 0; n--) {
            if(v[f_seq[n]].color == white) {
                v[f_seq[n]].pre = n;
                ll cnt = DFS_visit(f_seq[n], way);
                ret += ( cnt * (cnt - 1) ) / 2;
            } 
        }
    }
    return ret;
}

int main()
{
    cin >> N >> M;
    for(int m = 1, from = 0, to = 0; m <= M; m++)
    {
        cin >> from >> to;
        v[from].to.push_back(to);
        v[to].from.push_back(from);
    }
    DFS(normal);
    cout << DFS(transpose) << "\n";
    return 0;
}