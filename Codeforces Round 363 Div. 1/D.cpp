#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
struct point {
    LL x, y;
} a[10], m[1010];
struct vec {
    LL x, y, len, p;
    vec(LL _x = 0, LL _y = 0, LL _p = 0, LL _len = 0) {
        x = _x, y = _y, p = _p, len = _len;
    }
    bool operator < (const vec &b) const {
        if (x < b.x) return 1;
        if (x > b.x) return 0;
        if (y < b.y) return 1;
        if (y > b.y) return 0;
        return (len < b.len);
    }
    bool operator == (const vec &b) const {
        return ((x == b.x) && (y == b.y));
    }
    bool operator != (const vec &b) const {
        return ((x != b.x) || (y != b.y));
    }
} t[10][1010];
int n, k, num, l[10], h[1010], G[10][1010];
map<pair<LL, LL>, int> f[10];
set<int> s;

LL gcd(LL x, LL y) {
    return abs(__gcd(x, y));
}

void prepare() {
    for(int i = 1; i <= k; i++) {
        for(int j = 1; j <= n; j++) {
            LL tx = m[j].x - a[i].x, ty = m[j].y - a[i].y, g = gcd(tx, ty);
            t[i][j] = vec(tx / g, ty / g, j, tx * tx + ty * ty);
            G[i][j] = g;
        }
        sort(t[i] + 1, t[i] + 1 + n);
        for(int j = 1; j <= n; j++)
            if (t[i][j] != t[i][j - 1])
                f[i][make_pair(t[i][j].x, t[i][j].y)] = j;
    }
}

int hit(set<int> s, int num) {
    if (s.empty()) return 1;
    if (s.size() > num) return 0;
    int b = *s.begin(), ret = 0;
    s.erase(s.begin());
    for(int i = 1; i <= k; i++)
        if ((!ret) && (!l[i])) {
            LL tx = m[b].x - a[i].x, ty = m[b].y - a[i].y, g = G[i][b];
            int p = f[i][make_pair(tx / g, ty / g)];
            vec tmp = vec(tx / g, ty / g, 0, 0);
            set<int> s_n = s;
            for(; tmp == t[i][p]; p++) {
                int x = t[i][p].p;
                if ((x == b) || (s_n.size() > num)) break;
                if (!h[x]) s_n.insert(x);
            }
            l[i] = 1, h[b] = 1;
            ret = hit(s_n, num - 1);
            l[i] = 0, h[b] = 0;
        }
    return ret;
}

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> k >> n;
    for(int i = 1; i <= k; i++) cin >> a[i].x >> a[i].y;
    for(int i = 1; i <= n; i++) cin >> m[i].x >> m[i].y;
    prepare();
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        s.clear(), s.insert(i);
        ans += hit(s, k);
    }
    cout << ans << endl;
}
