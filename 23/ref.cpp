#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>
#include <climits>
#include <bits/stdc++.h>

#define inf LLONG_MAX
using namespace std;
struct edge{
	long long adj, c, l;
	long long cost;
};
struct node{
	vector <edge> EDGE;
	long long longest, cost;
};
struct cmp {
    bool operator()(edge a, edge b) {
        if(a.l > b.l) return 1;
        else if(a.l == b.l && a.cost > b.cost) return 1;
        return 0;
    }
};
bool visited[400050] = {};
int main(){
	long long n, m, a, b, c;
	priority_queue <edge, vector<edge>, cmp> pq;
	cin >> n >> m;
	node *nodes = (node *)malloc(sizeof(node) * (n + 2));
	for(int i = 0; i < m; i ++)
	{
		edge temp;
		cin >> a >> b >> temp.l >> temp.c;
		temp.adj = a;
		nodes[b].EDGE.push_back(temp);
		temp.adj = b;
		nodes[a].EDGE.push_back(temp);
	}
	long long num = 0, root = 0, sum = 0;
	nodes[root].longest = nodes[root].cost = 0;
	while(num != n)
	{
		while (nodes[root].EDGE.size() > 0)
		{
			edge e = nodes[root].EDGE.back();
			if(e.l > nodes[root].longest) e.cost = e.c;
			else if(e.l == nodes[root].longest) e.cost = nodes[root].cost + e.c;
			else e.cost = nodes[root].cost;
			pq.push(e); nodes[root].EDGE.pop_back();
		}
		visited[root] = true;
		while(pq.size() > 0)
		{
			edge top = pq.top();
			long long origin = root;
			root = top.adj;
			if(visited[top.adj]){pq.pop(); continue;}
			nodes[root].cost = top.cost;
			nodes[root].longest = (top.l > nodes[origin].longest)? top.l : nodes[origin].longest;
			sum += top.cost;
			pq.pop();
			break;
		}
		num ++;
	}
	// for(int i = 0; i < n; i ++) cout << nodes[i].cost << endl;
	cout << sum << endl;
}