#include <bits/stdc++.h>
#include <string>
using namespace std;
typedef long long ll;
#define MAXM (1 << 20)
const string put = "PUT", take = "TAKE", cc = "CC", dd = "DD";


struct node{
    int i;
    ll w, w_sum;
};
bool i_cmp(node &lhs, node &rhs)
{
    return lhs.i < rhs.i; 
}
bool w_cmp(node &lhs, node &rhs)
{
    return lhs.w < rhs.w; 
}
node nodes[MAXM];
int cnt;
int i;

void PUT()
{
    cin >> nodes[cnt].w;
    nodes[cnt].w_sum = nodes[cnt - 1].w_sum + nodes[cnt].w;
    nodes[cnt].i = i++;
    cnt++;
}
void TAKE()
{
    cout << nodes[--cnt].w << "\n";
}
void CC()
{
    int x, k, take_cnt;
    ll ret = 0;
    cin >> x >> k;
    take_cnt = (x % k) ? (x / k + 1) : (x / k);
    sort(nodes + cnt - x, nodes + cnt, w_cmp);
    for(int i = 0; i < take_cnt; i++) {
        ret += nodes[--cnt].w;
    }
    sort(nodes + cnt + take_cnt - x, nodes + cnt, i_cmp);
    for(int i = cnt + take_cnt - x; i < cnt; i++) {
        nodes[i].w_sum = nodes[i - 1].w_sum + nodes[i].w;
    }
    cout << ret << "\n";
}
void DD()
{
    int x;
    cin >> x;
    ll ret = nodes[cnt - 1].w_sum - nodes[cnt - 1 - x].w_sum;
    cout << ret << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int M;
    cin >> M;
    cnt++;
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