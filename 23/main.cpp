#include <bits/stdc++.h>
using namespace std;

const int MAX = 4e5 + 50;
typedef long long ll;

struct edge {
    ll to, len, toll, real_toll;
};
struct cmp_edge {
    bool operator()(edge lhs, edge rhs)
    {
        if(lhs.len == rhs.len)  return lhs.real_toll > rhs.real_toll;
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

int main()
{
    cin >> N >> M;
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
    ll ret = 0, root = 0, n = 0, prev = 0;
    priority_queue <edge, vector<edge>, cmp_edge> pq;
    while(n < N) {
        while(nodes[root].nei.size()) {
            buf_edge = nodes[root].nei.back();
            buf_edge.real_toll = 0;
            if(buf_edge.len >= nodes[root].max_len) buf_edge.real_toll += buf_edge.toll;
            if(buf_edge.len <= nodes[root].max_len) buf_edge.real_toll += nodes[root].toll;
            pq.push(buf_edge);
            nodes[root].nei.pop_back();
        }
        nodes[root].visited = true;
        while(pq.size()) {
            buf_edge = pq.top();
            prev = root;
            root = buf_edge.to;
            if(nodes[root].visited) pq.pop();
            else {
                nodes[root].toll = buf_edge.real_toll;
                nodes[root].max_len = max(nodes[prev].max_len, buf_edge.len);
                ret += buf_edge.real_toll;
                //cout << ret << "\n";
                pq.pop();
                break;
            }
        }
        n++;
    }
    cout << ret << "\n";
    return 0;
}