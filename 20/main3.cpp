#include <bits/stdc++.h>
#include <string>
using namespace std;
typedef long long ll;
#define MAXM (1 << 20)

const string put = "PUT", take = "TAKE", cc = "CC", dd = "DD";
struct node {
    int i;
    ll w;
    ll w_sum;
};
bool i_cmp(node &lhs, node &rhs)
{
    return lhs.i < rhs.i; 
}
bool w_cmp(node &lhs, node &rhs)
{
    return lhs.w < rhs.w; 
}

node buf;
vector<node> nodes;
int cnt;
void print_nodes(string buf)
{
    cout << buf << "\n";
    int size = nodes.size();
    for(int s = 0; s < size; s++) {
        cout << nodes[s].w << " ";
    }
    cout << "\n";
    for(int s = 0; s < size; s++) {
        cout << nodes[s].w_sum << " ";
    }
    cout << "\n";
}

void PUT()
{
    buf.i = cnt++;
    ll w;
    cin >> buf.w;
    buf.w_sum = nodes.back().w_sum + buf.w;
    nodes.push_back(buf);
    print_nodes("PUT");
}
void TAKE()
{
    cout << nodes.back().w << "\n";
    nodes.pop_back();
    print_nodes("TAKE");
}
void CC()
{
    int x, k, take_cnt, size = nodes.size();
    ll ret = 0;
    cin >> x >> k;
    take_cnt = (x % k) ? (x / k + 1) : (x / k);
    sort(nodes.end() - x, nodes.end(), w_cmp);
    print_nodes("CC1");
    for(int i = 0; i < take_cnt; i++) {
        ret += nodes.back().w;
        nodes.pop_back();
    }
    sort(nodes.end() - x, nodes.end(), i_cmp);
    // for(int i = size - x; i < size - take_cnt; i++) {
    //     nodes[i].w_sum = nodes[i - 1].w_sum + nodes[i].w;
    // }
    print_nodes("CC2");
    cout << ret << "\n";
}
void DD()
{
    int x, N = nodes.size();
    cin >> x;
    print_nodes("DD");
    ll ret = nodes[nodes.size() - 1].w_sum;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int M;
    cin >> M;
    nodes.push_back(buf);
    string buff;
    for(int m = 0; m < M; m++) {
        cin >> buff;
        if(buff == put)       PUT();
        else if(buff == take) TAKE();
        else if(buff == cc)   CC();
        else if(buff == dd)   DD();
    }
    return 0;
}