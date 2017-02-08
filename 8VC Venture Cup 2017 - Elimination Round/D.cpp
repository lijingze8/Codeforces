#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
int n, k;

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> n >> k, k = min(k, n - k);
    int x = 1, d = 1;LL ans = 1;
    for(int i = 1; i <= n; i++) {
        int nx = x + k;
        if (nx > n) nx -= n, d++, ans += d, d++;
        else ans += d;
        x = nx, ans -= (i == n);
        cout << ans << " ";
    }
}
