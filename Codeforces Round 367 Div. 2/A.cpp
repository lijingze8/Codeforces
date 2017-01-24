#include<bits/stdc++.h>
using namespace std;

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    int x, y, n, tx, ty, v;
    cin >> x >> y >> n;
    double ans = 1e+18;
    for(int i = 1; i <= n; i++) {
        cin >> tx >> ty >> v;
        ans = min(ans, sqrt(pow(x - tx, 2) + pow(y - ty, 2)) / v);
    }
    printf("%.10f", ans);
}
