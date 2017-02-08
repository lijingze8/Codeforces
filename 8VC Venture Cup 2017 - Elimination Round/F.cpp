#include<bits/stdc++.h>
#define N 1000010
using namespace std;
int h[N], v[N], c[N], cnt[N];
int tot, n, k;

void cyc() {
    int p = 1;tot = 0;
    for(int i = 1; i <= n; i++) h[i] = 1;
    for(int i = 1; i <= n; i++)
        if (h[i]) {
            p = i;int num = 0;
            while (h[p]) num++, h[p] = 0, p = v[p];
            c[++tot] = num;
        }
    for(int i = 1; i <= tot; i++) cnt[c[i]]++;
}

int Max() {
    int r = 0, t = k, ans = 0;
    for(int i = 1; i <= tot; i++) r += (c[i] % 2);
    for(int i = 1; i <= tot; i++) {
        int tmp = min(t, c[i] / 2);
        ans += tmp * 2, t -= tmp;
        if (t <= 0) break;
    }
    if (t > 0) ans += min(t, r);
    return ans;
}

int Min() {
    bitset<N> b;b[0] = 1;
    for(int i = 1; i <= n; i++) {
        if (cnt[i] == 0) continue;
        int bs = 1, tmp = cnt[i];
        while (tmp > bs) {
            b |= (b << (i * bs)), tmp -= bs, bs *= 2;
        }
        b |= (b << (i * tmp));
    }
    return k + (b[k] != 1);
}

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> n >> k;
    for(int i = 1; i <= n; i++) scanf("%d", &v[i]);
    cyc();
    cout << Min() << " " << Max() << endl;
}
