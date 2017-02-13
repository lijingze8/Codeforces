#include<bits/stdc++.h>
using namespace std;
int n, k, a[100010];

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> n >> k;
    int ans = n * 2 - k, m, p;
    for(int i = 1; i <= k; i++) {
        cin >> m;
        for(int j = 1; j <= m; j++) cin >> a[j];
        if (a[1] == 1) {
            p = 2;
            while (p <= m) {
                if (a[p] != p) break;
                p++;
            }
            p -= (a[p] != p);
            cout << ans - 2 * p + 1 << endl;
        }
    }
}
