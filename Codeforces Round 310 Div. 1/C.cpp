#include<bits/stdc++.h>
#define lb lower_bound
using namespace std;
struct bl {
    int l, r, U, L;
    bl(int _l, int _r, int _U, int _L) {
        l = _l, r = _r, U = _U, L = _L;
    }
    bool operator < (const bl &b) const {
        return r < b.r;
    } 
};
set<bl> s;
map<int, int> m;
int ql, qr, n, q;
char p;

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    cin >> n >> q;
    s.insert(bl(1, n, 1, 1));
    for(int i = 1; i <= q; i++) {
        scanf("%d %d %c", &ql, &qr, &p);
        if (m[ql] > 0) {
            cout << 0 << endl;continue;
        } else m[ql]++;
        set<bl> :: iterator it = s.lb(bl(0, ql, 0, 0));
        bl tmp = *it;s.erase(it);
        if (p == 'U') {
            cout << qr - tmp.U + 1 << endl;
            s.insert(bl(tmp.l, ql - 1, tmp.U, tmp.L));
            s.insert(bl(ql + 1, tmp.r, tmp.U, ql + 1));
        } else {
            cout << ql - tmp.L + 1 << endl;
            s.insert(bl(tmp.l, ql - 1, qr + 1, tmp.L));
            s.insert(bl(ql + 1, tmp.r, tmp.U, tmp.L));
        }
    }
}
