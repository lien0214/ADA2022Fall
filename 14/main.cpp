#include <bits/stdc++.h>
using namespace std;
#define MAXN 1024
#define MAXK 512
typedef long long ll;

int N, K;
ll a[MAXN];
ll mdv[MAXN][MAXN]; //max discomfort value * (r - l + 1) [l, r]
ll md[MAXN][MAXK];  //min discomfort k: 0-based

void fill_mdv()
{
    ll curr_total;
    for(int l = 0; l < N; l++) {
        curr_total = 0;
        for(int r = l; r < N; r++) {
            mdv[l][r] = curr_total += a[r];
            if(r > l)   mdv[l][r] = max(mdv[l][r - 1], mdv[l][r]);
            curr_total = max(curr_total, (ll)0); 
        }
        for(int r = l + 1; r < N; r++)
            mdv[l][r] *= (r - l + 1);
    }
}

void fill_md()
{
    for(int k = 0; k < K; k++) {
        for(int n = 0; n < N; n++) {
            if(n < k)   md[n][k] = 0;
            else if(k == 0) md[n][k] = mdv[0][n];
            else {
                for(int s = 0; s < n; s++) {
                    md[n][k] = (s == 0) ?
                        md[s][k - 1] + mdv[s + 1][n] :
                        min(md[n][k], md[s][k - 1] + mdv[s + 1][n]);
                }
            }
        }
    }
}

int main()
{
    cin >> N >> K;
    for(int n = 0; n < N; n++)
        cin >> a[n];
    fill_mdv();
    fill_md();
    cout << md[N - 1][K - 1] << "\n";
    return 0;
}
