#include <bits/stdc++.h>
#include <climits>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> iPair;
#define MAXN (1 << 12)
#define INF LLONG_MAX

ll N, M;
vector<iPair> adj[MAXN];

ll shortestPath(int src)
{
	priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
	vector<ll> dist(N + 1, INF);
	pq.push(make_pair(0, src));
	dist[src] = 0;
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();

		// Get all adjacent of u.
		for (auto x : adj[u]) {
			int v = x.first;
			int weight = x.second;
			if (dist[v] > dist[u] + weight) {
				// Updating distance of v
				dist[v] = dist[u] + weight;
				pq.push(make_pair(dist[v], v));
			}
		}
	}
    ll ret = 0;
    for(int i = 1; i <= N; i++) {
        //cout << i << " " << dist[i] << "\n";
        ret += dist[i];
    }
    //cout << ret << "\n";
    return ret;
}

int main()
{
    //input
    cin >> N >> M;
    ll from, to, w;
    for(int m = 0; m < M; m++) {
        cin >> from >> to >> w;
        adj[from].push_back(make_pair(to, w));
    }

    ll ret = LLONG_MAX;
    ll curr;
    for(int n = 2; n <= N; n++) {
        adj[1].push_back(make_pair(n, 0));
        curr = shortestPath(1);
        ret = (ret < curr) ? ret : curr;
        adj[1].pop_back();
    }
    cout << ret << "\n";
    return 0;
}