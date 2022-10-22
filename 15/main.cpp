#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MAX (1 << 17)

int N;
struct p {
    ll a;
    ll b;
}people[MAX];
p* m[MAX] = {people};
struct gp {
    int n;
    ll a_total, total;
}grp[MAX];

bool cmp_p(const p lhs, const p rhs)
{
    return (lhs.b == rhs.b) ? (lhs.a > rhs.a) : (lhs.b > rhs.b);
}
bool cmp_gp(const gp lhs, const gp rhs)
{
    return lhs.a_total * rhs.n < rhs.a_total * lhs.n;
}
void print_m()
{
    cout << "a.b\n";
    for(int n = 0; n < N; n++) {
        cout << grp[n].n << " ";
        for(int g = 0; g < grp[n].n; g++)
            cout << m[n][g].a << "." << m[n][g].b << " ";
        cout << "\n";
    }
}
void print_grp()
{
    cout << "\n";
    for(int n = 0; n < N; n++)
        printf("%d group %d people %lld a_total %lld total\n",
                     n, grp[n].n, grp[n].a_total, grp[n].total);
}

int main()
{
    cin >> N;
    for(int n = 0; n < N; n++) {
        cin >> grp[n].n;
        m[n + 1] = m[n] + grp[n].n;
        for(int i = 0; i < grp[n].n; i++)
            cin >> m[n][i].a >> m[n][i].b;
        sort(m[n], m[n] + grp[n].n, cmp_p);

        for(int i = 0; i < grp[n].n; i++) {
            grp[n].a_total += m[n][i].a;
            grp[n].total = max(grp[n].total, grp[n].a_total + m[n][i].b);
        }
    }
    //print_m();
    sort(grp, grp + N, cmp_gp);
    //print_grp();
    ll ret = 0, a_total = 0;
    for(int n = 0; n < N; n++) {
        ret += grp[n].n * (a_total + grp[n].total);
        a_total += grp[n].a_total;
    }
    cout << ret << "\n";
    return 0;
}