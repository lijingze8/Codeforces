#include<bits/stdc++.h>
#define N 22
using namespace std;
double ans[N], p[N], s[1 << N], f[1 << N];
int n, k, a[1 << N], num;

void prepare() {
    for(int i = 0; i < (1 << n); i++) {
        s[i] = 1;
        for(int j = 0; j < n; j++) {
            int tmp = 1 << j;
            if ((i & tmp) > 0) a[i]++, s[i] -= p[j];
        }
    }
}

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> n >> k;
    for(int i = 0; i < n; i++) scanf("%lf", &p[i]), num += (p[i] != 0);
    k = min(num, k);
    prepare();
    f[0] = 1;
    for(int i = 0; i < (1 << n); i++) {
        if (a[i] >= k) continue;
        for(int j = 0; j < n; j++) {
            int tmp = 1 << j;
            if ((i & tmp) == 0) {
                double t = f[i] / s[i] * p[j];
                f[i + tmp] += t, ans[j] += t;
            }
        }
    }
    for(int i = 0; i < n; i++) printf("%.8f ", ans[i]);
}
