#include<bits/stdc++.h>
#define N 300010
#define ub upper_bound
typedef long long LL;
using namespace std;
struct br {
    LL len;int id;
    inline bool operator < (const br &b) const {
        return ((len < b.len) || ((len == b.len) && (id < b.id)));
    }
} b[N], tmp;
struct iv {
    LL l, r;int id;
    inline bool operator < (const iv &b) const {
        return ((r < b.r) || ((r == b.r) && (l < b.l)) || ((r == b.r) && (l == b.l) && (id < b.id)));
    }
} a[N];
set<br> s;
int n, m, p, ans[N];
LL l[N], r[N];

void No_answer() {
    cout << "No" << endl, exit(0);
}

int main() {
    cin >> n >> m;
    for(int i = 1; i <= n; i++) scanf("%I64d%I64d", &l[i], &r[i]);
    for(int i = 1; i < n; i++)
        a[i].l = l[i + 1] - r[i], a[i].r = r[i + 1] - l[i], a[i].id = i;
    for(int i = 1; i <= m; i++) 
        scanf("%I64d", &b[i].len), b[i].id = i;
    sort(a + 1, a + n);
    sort(b + 1, b + m + 1);
    p = 1;
    for(int i = 1; i < n; i++) {
        while ((p <= m) && (b[p].len <= a[i].r)) s.insert(b[p]), p++;
        tmp.len = a[i].l, tmp.id = 0;
        pan(i);
        set<br> :: iterator it = s.ub(tmp);
        if ((it == s.end()) || ((*it).len < a[i].l)) No_answer(); //!!!
        ans[a[i].id] = (*it).id, s.erase(it);
    }
    cout << "Yes" << endl;
    for(int i = 1; i < n; i++) printf("%d ", ans[i]);
}
