#include <bits/stdc++.h>
using namespace std;
#define MAXN (1 << 19)
#define MINS 45
#define MAXS 123
typedef long long ll;

char str[MAXN];
int N;
ll K;
queue<ll> Ktable[MAXS];
ll minus_table[MAXS];
ll cnt[MAXS];
int main()
{
    cin >> str >> K;
    N = strlen(str);
    for(int n = 0, c = 0; n < N; n++, c = 0) {
        for(int s = MAXS; s > str[n]; s--)
            c += cnt[s];
        cnt[str[n]]++;
        Ktable[str[n]].push(c);
    }
    for(int n = 0; n < N; n++) {
        int s = MINS;
        while(Ktable[s].empty() || Ktable[s].front() - minus_table[s] > K)
            minus_table[s++]++;
        K -= (Ktable[s].front() - minus_table[s]);
        Ktable[s].pop();
        str[n] = s;
    }
    cout << str << "\n";
    return 0;
}