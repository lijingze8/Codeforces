#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define INF 1000000000
#define N 200010
using namespace std;
struct rec {
    int smin, smax, tmin, tmax;
} a[N];
vector< pair<int, int> > v[N];
vector<int> t[N];
int ex[N], ey[N], dfn[N], low[N], s_min[N][20], s_max[N][20], t_min[N][20], t_max[N][20], st[N], mark[N], tree[N], num[N], ed[N];
int cur, tot, top, cnt, tot_tree, n, m, q, x, y;
    
void Tarjan(int x, int from) {
    dfn[x] = low[x] = ++cur, st[++top] = x;
    for(int i = 0; i < v[x].size(); i++) {
        int tmp = v[x][i].fi;
        if (v[x][i].se == from) continue;
        if (dfn[tmp]) low[x] = min(low[x], dfn[tmp]);
        else Tarjan(tmp, v[x][i].se), low[x] = min(low[x], low[tmp]);
    }
    if (dfn[x] == low[x]) {
        int tmp;cnt++;
        do {
            tmp = st[top--], mark[tmp] = cnt;
        } while (tmp != x);
    }
}

void DFS(int x, int fa, int tot_tree) {
    num[x] = ++tot, tree[tot] = tot_tree;
    for(int i = 0; i < t[x].size(); i++) {
        int tmp = t[x][i];
        if (tmp == fa) continue;
        DFS(tmp, x, tot_tree);
    }
    ed[x] = tot;
}

void prepare() {
    int U = (int)(log(cnt) / log(2) + 1);
    for(int i = 1; i <= cnt; i++)
        s_min[i][0] = a[i].smin, s_max[i][0] = a[i].smax, t_min[i][0] = a[i].tmin, t_max[i][0] = a[i].tmax;
    for(int i = 1; i <= U; i++)
        for(int j = 1; j <= cnt; j++) {
            int tmp = 1 << (i - 1);
            s_min[j][i] = min(s_min[j][i - 1], s_min[j + tmp][i - 1]);
            s_max[j][i] = max(s_max[j][i - 1], s_max[j + tmp][i - 1]);
            t_min[j][i] = min(t_min[j][i - 1], t_min[j + tmp][i - 1]);
            t_max[j][i] = max(t_max[j][i - 1], t_max[j + tmp][i - 1]);
        }
}

rec cal(int l, int r) {
    if (l == r) return a[l];
    int tmp = (int)(log(r - l) / log(2)), len = 1 << tmp;
    rec ret;
    ret.smin = min(s_min[l][tmp], s_min[r - len + 1][tmp]);
    ret.smax = max(s_max[l][tmp], s_max[r - len + 1][tmp]);
    ret.tmin = min(t_min[l][tmp], t_min[r - len + 1][tmp]);
    ret.tmax = max(t_max[l][tmp], t_max[r - len + 1][tmp]);
    return ret;
}

void No_Answer() {
    cout << "No" << endl;exit(0);
}

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> n >> m >> q;
    for(int i = 1; i <= m; i++) {
        cin >> ex[i] >> ey[i];
        v[ex[i]].pb(mp(ey[i], i)), v[ey[i]].pb(mp(ex[i], i));
    }
    for(int i = 1; i <= n; i++)
        if (!mark[i]) Tarjan(i, 0);
    for(int i = 1; i <= m; i++) {
        int x = mark[ex[i]], y = mark[ey[i]];
        if (x == y) continue;
        t[x].pb(y), t[y].pb(x);
    }
    for(int i = 1; i <= cnt; i++)
        if (!num[i]) DFS(i, 0, ++tot_tree);
    for(int i = 1; i <= cnt; i++)
        a[i].smin = a[i].tmin = INF, a[i].smax = a[i].tmax = -INF;
    for(int i = 1; i <= q; i++) {
        cin >> x >> y, x = num[mark[x]], y = num[mark[y]];
        if (x == y) continue;
        if (tree[x] != tree[y]) No_Answer();
        a[y].smin = min(x, a[y].smin), a[y].smax = max(x, a[y].smax);
        a[x].tmin = min(y, a[x].tmin), a[x].tmax = max(y, a[x].tmax);
    }
    prepare();
    for(int i = 1; i <= cnt; i++) {
        rec tmp = cal(num[i], ed[i]);
        bool p1 = (tmp.smin < num[i]) || (tmp.smax > ed[i]), p2 = (tmp.tmin < num[i]) || (tmp.tmax > ed[i]);
        if (p1 && p2) No_Answer(); 
    }
    cout << "Yes" << endl;
}
