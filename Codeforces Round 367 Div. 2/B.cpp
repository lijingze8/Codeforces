#include<bits/stdc++.h>
using namespace std;
int n, q, x, a[100010];

int find(int x) {
    int l = 0, r = n, ans = 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid] <= x) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ans;
}

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> n;
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    sort(a + 1, a + 1 + n), a[0] = -1;
    cin >> q;
    for(int i = 1; i <= q; i++) {
        scanf("%d", &x);
        printf("%d\n", find(x));
    }
}
