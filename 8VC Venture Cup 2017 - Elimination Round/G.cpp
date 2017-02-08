#include<bits/stdc++.h>
#define Mo 998244353
#define G 3
#define N (1 << 17)
typedef long long LL;
using namespace std;
int r[N], n, k, tot, s;
LL w[20], iw[20], f1[N], f2[N], f3[N], g[6][N], inv;

void cp(LL *A, LL *B) {
    for(int i = 0; i < tot; i++) A[i] = B[i];
}

LL Pow(LL x, int p) {
    LL ret = 1;
    for(; p > 0; p >>= 1, x = (x * x) % Mo)
        if (p & 1 == 1) ret = (ret * x) % Mo;
    return ret;
}

void init() {
    cin >> n >> k;
    for(tot = 1, s = 0; tot < k + k + 2; tot <<= 1, s++);
    for(int i = 1; i < tot; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << s - 1);
    inv = Pow(tot, Mo - 2), w[s] = Pow(G, (Mo - 1) / tot), iw[s] = Pow(w[s], Mo - 2);
    for(int i = s - 1; i >= 1; i--) w[i] = (w[i + 1] * w[i + 1]) % Mo;
    for(int i = s - 1; i >= 1; i--) iw[i] = (iw[i + 1] * iw[i + 1]) % Mo;
}

void prepare() {
    f1[0] = f2[0] = 0, f3[0] = 1;
}

void recur() {
    g[1][0] = 1;
    for(int i = 1; i < tot; i++)
        g[1][i] = (f3[i] + f3[i - 1]+ f2[i - 1]) % Mo;
    cp(f1, f2), cp(f2, f3), cp(f3, g[1]);
    for(int i = k + 1; i < tot; i++) f1[i] = f2[i] = f3[i] = 0;
}

void NTT(LL *A, int n, int op) {
    for(int i = 0; i < n; i++)
        if (i < r[i]) swap(A[i], A[r[i]]);
    for(int len = 2, s = 1; len <= n; len <<= 1, s++) {
        LL w0 = (op == 1) ? w[s] : iw[s], tmp = 1;
        for(int i = 0; i < n; i += len, tmp = 1)
            for(int j = 0; j < (len >> 1); j++) {
                LL x = A[i + j], y = 1LL * tmp * A[i + j + (len >> 1)] % Mo;
                A[i + j] = (x + y) % Mo;
                A[i + j + (len >> 1)] = ((x - y) % Mo + Mo) % Mo;
                tmp = tmp * w0 % Mo;
            }
    }
}

void work() {
    int U = 0;for(int tmp = n; tmp > 0; tmp >>= 1, U++);
    recur();
    for(int s = U - 2; s >= 0; s--) {
        NTT(f1, tot, 1), NTT(f2, tot, 1), NTT(f3, tot, 1);
        for(int i = 0; i < tot; i++) g[1][i] = f3[i] * f3[i] % Mo;
        for(int i = 0; i < tot; i++) g[2][i] = f2[i] * f2[i] % Mo;
        for(int i = 0; i < tot; i++) g[3][i] = f3[i] * f2[i] % Mo;
        for(int i = 0; i < tot; i++) g[4][i] = f2[i] * f1[i] % Mo;
        for(int i = 0; i < tot; i++) g[5][i] = f1[i] * f1[i] % Mo;
        for(int i = 1; i <= 5; i++) NTT(g[i], tot, -1);
        for(int i = 1; i <= 5; i++)
            for(int j = 0; j < tot; j++)
                g[i][j] = g[i][j] * inv % Mo;
        cp(f3, g[1]), cp(f2, g[3]), cp(f1, g[2]);
        for(int i = 0; i < tot; i++) f3[i] = (f3[i] + g[2][i - 1]) % Mo;
        for(int i = 0; i < tot; i++) f2[i] = (f2[i] + g[4][i - 1]) % Mo;
        for(int i = 0; i < tot; i++) f1[i] = (f1[i] + g[5][i - 1]) % Mo;
        for(int i = k + 1; i < tot; i++) f1[i] = f2[i] = f3[i] = 0;
        if ((n & (1 << s)) > 0) recur();
    }
    for(int i = 1; i <= k; i++) printf("%d ", (i > n) ? 0 : f3[i]);
}

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    init();
    prepare();
    work();
}
