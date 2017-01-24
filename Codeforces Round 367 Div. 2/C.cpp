#include<bits/stdc++.h>
#define N 100010
#define INF (1LL << 60)
typedef long long LL;
using namespace std;
string s[N], t[N];
int n, a[N];
LL f[N][2];

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> n;
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++)
        cin >> s[i], t[i] = s[i], reverse(t[i].begin(), t[i].end());
    for(int i = 1; i <= n; i++) f[i][0] = f[i][1] = INF;
    f[1][0] = 0, f[1][1] = a[1];
    for(int i = 2; i <= n; i++) {
        if (s[i] >= s[i-1]) f[i][0] = min(f[i][0], f[i-1][0]);
        if (s[i] >= t[i-1]) f[i][0] = min(f[i][0], f[i-1][1]);
        if (t[i] >= s[i-1]) f[i][1] = min(f[i][1], f[i-1][0] + a[i]);
        if (t[i] >= t[i-1]) f[i][1] = min(f[i][1], f[i-1][1] + a[i]);
    }
    LL ans = min(f[n][0], f[n][1]);
    if (ans >= INF) cout << -1 << endl;
    else cout << ans << endl;
}
