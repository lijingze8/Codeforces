#include<bits/stdc++.h>
using namespace std;
int n, k;

void pr(int x, int y) {
    cout << x << " " << y << endl;
}

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> n >> k;
    if ((k == 1) || (k > 3)) cout << -1 << endl;
    if (k == 2)
        if (n <= 4) cout << -1 << endl;
        else {
            cout << n - 1 << endl;
            for(int i = 1; i < n; i++) pr(i, i + 1);
        }
    if (k == 3) {
        if (n < 4) cout << -1 << endl;
        else if (n == 4) cout << 3 << endl, pr(1, 2), pr(2, 3), pr(3, 4);
        else {
            cout << n << endl;
            pr(1, 2), pr(2, 3), pr(3, 4), pr(1, 5), pr(3, 5);
            for(int i = 6; i <= n; i++) pr(5, i);
        }
    }
}
