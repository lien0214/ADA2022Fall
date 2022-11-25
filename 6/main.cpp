#include <bits/stdc++.h>
using namespace std;
#define MAX (1 << 21)
typedef long long ll;

struct edge{
    int v1, v2;
    ll w;
}edges[MAX];
int diset[MAX];
int cnt = 1;
bool edge_cmp(edge lhs, edge rhs)
{
    if(lhs.w == rhs.w)  return lhs.v1 <= rhs.v1;
    else                return lhs.w <= rhs.w;
}
void path_compression(int v)
{
    int _v, dis = v;
    while(diset[dis] != dis) dis = diset[dis];
    while(diset[v] != dis) {
        _v = v;
        v = diset[v];
        diset[_v] = dis;
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int V, E;
    ll ret = 0;
    cin >> V >> E;
    for(int v = 1; v <= V; v++)
        diset[v] = v;
    for(int e = 0; e < E; e++)
        cin >> edges[e].v1 >> edges[e].v2 >> edges[e].w;
    sort(edges, edges + E, edge_cmp);
    for(int e = 0, v1, v2; e < E; e++) {
        v1 = edges[e].v1, v2 = edges[e].v2;
        path_compression(v1);
        path_compression(v2);
        if(diset[v1] == diset[v2]) continue;
        diset[diset[v2]] = diset[v1];
        ret += edges[e].w;
    }
    cout << ret << "\n";
    return 0;
}