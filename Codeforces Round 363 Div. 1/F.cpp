#include<bits/stdc++.h>
#define Mo 1000000007
#define pb push_back
#define N 1000010
typedef long long LL;
using namespace std;
vector<int> v[N];
LL JC[N];
int num_p[N], num_m[N], a[N], m[N], f[N], g[N], n;

void prepare() {
    JC[0] = 1;
    for(int i = 1; i <= n; i++) JC[i] = (JC[i - 1] * i) % Mo;
    for(int i = 1; i <= n; i++) m[i] = 1;
    for(int i = 2; i <= n; i++)
        if (v[i].size() == 0) {
            num_p[n / i]++;
            for(int j = i; j <= n; j += i)
                v[j].pb(i), m[j] *= i;
        }
    for(int i = 1; i <= n; i++) num_m[m[i]]++;
    num_p[1]++, v[1].pb(1);
 }

void No_answer() {
    cout << 0 << endl;
    exit(0);
}

int get_num(int x) {
    return (x == 1) ? 1 : (n / x);
}

int pan(int a, int b) {
    if (v[a].size() != v[b].size()) return 0;
    for(int i = 0; i < v[b].size() - 1; i++)
        if (v[a][i] != v[b][i]) return 0;
    //There is at most one which > sqrt(n)
    int x = v[a].back(), y = v[b].back();
    if (get_num(x) != get_num(y)) return 0;
    if ((f[y] > 0) && (f[y] != x)) return 0;
    if ((g[x] > 0) && (g[x] != y)) return 0;
    if ((f[y] == 0) && (g[x] == 0)) num_p[get_num(x)]--;
    f[y] = x, g[x] = y;
}

//suppose f[i] to be the prime on i now
//suppose g[i] to be the prime i's location now
int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> n;
    prepare();
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++) {
        if (a[i] == 0) continue;
        num_m[m[a[i]]]--;
        if (!pan(a[i], i)) No_answer();
    }
    LL ans = 1;
    for(int i = 1; i <= n; i++)
        ans = ans * JC[num_p[i]] % Mo * JC[num_m[i]] % Mo;
    cout << ans << endl;
}
