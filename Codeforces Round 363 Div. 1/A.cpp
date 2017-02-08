#include<bits/stdc++.h>
#define INF 10000
#define N 200
using namespace std;
int n, f[N][3], a[N];

int Min(int a, int b, int c) {
    return min(a, min(b, c));
}

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    //0 for contest, 1 for sports, 2 for rest
    for(int i = 1; i <= n; i++) {
        if (a[i] == 0) f[i][0] = f[i][1] = INF;
        if (a[i] == 1) {
            f[i][0] = min(f[i - 1][1], f[i - 1][2]);
            f[i][1] = INF;
        }
        if (a[i] == 2) {
            f[i][0] = INF;
            f[i][1] = min(f[i - 1][0], f[i - 1][2]);
        }
        if (a[i] == 3) {
            f[i][0] = min(f[i - 1][1], f[i - 1][2]);
            f[i][1] = min(f[i - 1][0], f[i - 1][2]);
        }
        f[i][2] = Min(f[i - 1][0], f[i - 1][1], f[i - 1][2]) + 1;
    }
    cout << Min(f[n][0], f[n][1], f[n][2]) << endl;
}
