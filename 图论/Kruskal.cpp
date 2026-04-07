#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
int n, m;
int fa[N];
int find(int x) {
    if (x != fa[x])
        fa[x] = find(fa[x]);
    return fa[x];
}
void add(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        fa[x] = fa[y];
    }
}
const int M = 2e5 + 10;
struct edge {
    int u, v, val;
} ed[M];
bool cmp(edge a, edge b) { return a.val < b.val; }
int cnt;
int ans;
void Kruskal() {
    for (int i = 1; i <= m; i++) {
        edge now = ed[i];
        if (find(now.v) != find(now.u)) {
            fa[find(now.u)] = find(now.v);
            ans += now.val;
        }
    }
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int aa, bb, cc;
        cin >> aa >> bb >> cc;
        ed[++cnt].u = aa;
        ed[cnt].v = bb;
        ed[cnt].val = cc;
    }
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
    }
    sort(ed + 1, ed + m + 1, cmp);
    Kruskal();
    int aa = 0;
    for (int i = 1; i <= n; i++) {
        if (fa[i] == i)
            aa++;
        if (aa > 1) {
            cout << "orz";
            return 0;
        }
    }
    cout << ans;
    return 0;
}
