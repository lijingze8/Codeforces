#include<bits/stdc++.h>
#define N 4000000
#define M 31
typedef long long LL;
using namespace std;
int t[N][2], sum[N], b[M+1], q, tot = 1;

void Make_base() {
    b[0] = 1;
    for(int i = 1; i <= M; i++) b[i] = b[i-1] * 2;
}

void ins(int x) {
    int nw = 1;
    for(int i = M; i >= 0; i--) {
        int nx = (x & b[i]) > 0 ? 1 : 0;
        sum[nw]++;
        if (t[nw][nx] > 0) nw = t[nw][nx];
        else t[nw][nx] = ++tot, nw = tot;
    }
    sum[nw]++;
}

void del(int x) {
    int nw= 1;
    for(int i = M; i >= 0; i--) {
        int nx = (x & b[i]) > 0 ? 1 : 0;
        sum[nw]--, nw = t[nw][nx];
    }
    sum[nw]--;
}

int ask(int x) {
    int nw = 1, ans = 0;
    for(int i = M; i >= 0; i--) {
        int nx = (x & b[i]) > 0 ? 1 : 0;
        int w = (nx + 1) % 2;
        if (sum[t[nw][w]] > 0) ans += b[i], nw = t[nw][w];
        else nw = t[nw][nx];
    }
    return ans;
} 

int main() {
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
    Make_base();ins(0);
    scanf("%d\n", &q);
    for(int cs = 1; cs <= q; cs++) {
        char c = getchar();
        int x;scanf("%d\n", &x);
        if (c == '+') ins(x);
        if (c == '-') del(x);
        if (c == '?') printf("%d\n", ask(x));
    }
}
