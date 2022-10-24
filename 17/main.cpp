#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAXN 305
#define MAXK 305

int N, K, M;
ll table[3][MAXK][MAXK]; // n-th prefix sum with k move

int main()
{
    cin >> N >> K >> M;
    for(int a = 0; a <= K; a++)
        table[0][a][a] = 1;
    int from = 0, to = 1;
    for(int n = 1; n < N; n++) {
        for(int p = 0; p <= K; p++) {
            for(int k = p; k <= K; k++) {
                ll tmp = 0;
                int S = k - p;
                for(int i = 0; i <= p; i++)
                    tmp += table[from][i][i+S];
                for(int s = 1; s <= S; s++)
                    tmp += table[from][p+s][k];
                table[to][p][k] = tmp % M;
            }
        }
        from = to;
        to = (to + 1 == 3) ? 0 : (to + 1);
    }
    ll ret = 0;
    for(int p = 0; p <= K; p++)
        for(int k = p; k <= K; k++) {
            ret += table[from][p][k];
            ret = (ret > M) ? (ret - M) : ret;
        }
    cout << ret << "\n";
    return 0;
}