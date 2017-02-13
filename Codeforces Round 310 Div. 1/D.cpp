#include<bits/stdc++.h>
#define N 200010
using namespace std;
struct peg {
    int x, id;
    bool operator < (const peg &b) const {
        return x < b.x;
    }
} a[N];
int p, l, n, m, q[N], b[N];

int find_small(int x) {
    int l = 1, r = n, ans;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid].x <= x) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}

int find_large(int x) {
    int l = 1, r = n, ans;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid].x >= x) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    return ans;
}

int work(int p, int l) {
    int top, tmp;
    q[top = 1] = p, p = b[p];
    while (l > 0) {
        if ((top >= 3) && (q[top] == q[top - 1]) && (q[top] == q[top - 2]))
            return q[top];
        if ((top >= 3) && (q[top] == q[top - 2]))
            l = l % (2LL * abs(a[b[q[top]]].x - a[b[q[top - 1]]].x));
        if (top & 1 == 1) tmp = find_small(a[p].x + l);
        else tmp = find_large(a[p].x - l);
        l -= abs(a[p].x - a[tmp].x);
        p = tmp, q[++top] = a[p].id;
    }
    return a[p].id;
}

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) cin >> a[i].x, a[i].id = i;
    sort(a + 1, a + 1 + n);
    for(int i = 1; i <= n; i++) b[a[i].id] = i;
    for(int i = 1; i <= m; i++)
        cin >> p >> l, cout << work(p, l) << endl;
}
