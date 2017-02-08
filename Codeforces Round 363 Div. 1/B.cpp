#include<bits/stdc++.h>
#define N 200010
using namespace std;
int n, root, a[N], f[N];

int find(int x) {
    if (f[x] == x) return x;
    return f[x] = find(f[x]);
}

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> n;int num = 0;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) f[i] = i;
    for(int i = 1; i <= n; i++) if (a[i] == i) root = i;
    for(int i = 1; i <= n; i++) {
        int x = find(i), y = find(a[i]);
        if (x == y)
            if (root > 0) a[i] = root, num += (i != root);
            else root = i, num++, a[i] = i;
        else f[x] = y;
    }
    cout << num << endl;
    for(int i = 1; i <= n; i++) cout << a[i] << " ";
}
