#include<bits/stdc++.h>
#define N 22
using namespace std;
double c[30][30], s[1 << N], g[N], p[N];
int a[1 << N], n, k;

void prepare() {
    for(int i = 0; i <= 20; i++) c[i][0] = 1;
    for(int i = 1; i <= 20; i++)
        for(int j = 1; j <= 20; j++)
            c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
    for(int i = 0; i < (1 << n); i++)
        for(int j = 0; j < n; j++) {
            int tmp = 1 << j;
            if ((i & tmp) > 0) a[i]++, s[i] += p[j];
        }
    //O(n)'s algorithm
    //for(int i = 0; i < n; i++) s[1 << i] = a[i];
    //for(int i = 0; i < (1 << n); i++) {
    //    s[i] = s[i & (-i)] + s[i ^ (i & (-i))];
    //    a[i] = (i & 1) + a[i >> 1];
    //}
    for(int i = k - 1; i >= 0; i--) {
        g[i] = 1;
        for(int j = i + 1; j <= k - 1; j++)
            g[i] -= g[j] * c[(n - 1) - i][j - i];
    }
}

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> n >> k;int num = 0;
    for(int i = 0; i < n; i++) scanf("%lf", &p[i]), num += (p[i] != 0);
    k = min(num, k);
    prepare();
    for(int i = 0; i < n; i++) {
        double ret = 0;
        for(int j = 0; j < (1 << n); j++)
            if ((a[j] < k) && ((j & (1 << i)) == 0))
                ret += g[a[j]] / (1 - s[j]);
        printf("%.8f ", p[i] * ret);
    }
}
