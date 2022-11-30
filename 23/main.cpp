#include <bits/stdc++.h>
using namespace std;

#define MAX (1 << 19)
typedef long long ll;

struct edge {
    ll to, len, toll, cmp_toll;
};
struct cmp_edge {
    bool operator()(edge lhs, edge rhs)
    {
        if(lhs.len == rhs.len)  return lhs.toll > rhs.toll;
        return lhs.len > rhs.len;
    }
};
struct node {
    vector<edge> nei;
    ll toll, max_len;
    bool visited;
};
edge buf_edge;

node nodes[MAX];
ll N, M;

void make_edge(ll n1, ll n2, ll len, ll toll)
{
    buf_edge.to = n2;
    buf_edge.len = len;
    buf_edge.toll = toll;
    nodes[n1].nei.push_back(buf_edge);
    buf_edge.to = n1;
    nodes[n2].nei.push_back(buf_edge);
}
void print_edge()
{
    for(ll n = 0; n < N; n++) {
        for(auto x : nodes[n].nei) {
            cout << n << " " << x.to << " " << x.len << " " << x.toll << "\n";
        }
    }
}


int main()
{
    cin >> N >> M;
    priority_queue <edge, vector<edge>, cmp_edge> pq;
    for(ll n = 0; n < N; n++) {
        nodes[n].max_len = LLONG_MAX;
        nodes[n].toll = LLONG_MAX;
        nodes[n].visited = false;
    }
    ll n1, n2, len, toll;
    for(ll m = 0; m < M; m++) {
        cin >> n1 >> n2 >> len >> toll;
        make_edge(n1, n2, len, toll);
    }
    nodes[0].max_len = 0;
    nodes[0].toll = 0;
    ll ret = 0;
    for(ll n = 0, root = 0, prev = 0; n < N; n++) {
        nodes[root].visited = true;
        while(nodes[root].nei.size() > 0) {
            buf_edge = nodes[root].nei.back();
            buf_edge.cmp_toll = 
                (buf_edge.len >= nodes[root].max_len) ? buf_edge.toll : nodes[root].toll;
            if(buf_edge.len == nodes[root].max_len)
                buf_edge.cmp_toll += nodes[root].toll;
            pq.push(buf_edge);
            nodes[root].nei.pop_back();
        }
        while(pq.size() > 0) {
            buf_edge = pq.top();
            prev = root;
            root = buf_edge.to;
            if(!nodes[pq.top().to].visited) pq.pop();
            else break;
        }
        nodes[root].toll = buf_edge.cmp_toll;
        nodes[root].max_len = max(nodes[root].max_len, buf_edge.len);
        ret += buf_edge.cmp_toll;
        pq.pop();
    }
    cout << ret << "\n";
    return 0;
}