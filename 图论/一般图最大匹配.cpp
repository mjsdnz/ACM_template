#include <bits/stdc++.h>
using namespace std;
int n, m;
const int N = 1e3 + 10;
int fa[N];
int dfn[N];
int pre[N];
int cp[N];
vector<int> g[N];
int vis[N];
void add(int u, int v) { g[u].push_back(v); }
int tim;
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int lca(int x, int y) {
    ++tim;
    x = find(x);
    y = find(y);
    while (dfn[x] != tim) {
        dfn[x] = tim;
        x = find(pre[cp[x]]);
        if (y)
            swap(x, y);
    }
    return x;
}
queue<int> q;
void blossom(int x, int y, int w) {
    while (find(x) != w) {
        pre[x] = y;
        y = cp[x];
        if (vis[y] == 2)
            vis[y] = 1, q.push(y);
        if (find(x) == x)
            fa[x] = w;
        if (find(y) == y)
            fa[y] = w;
        x = pre[y];
    }
}
bool work(int s) {
    for (int i = 1; i <= n; i++)
        fa[i] = i, vis[i] = pre[i] = 0;
    while (!q.empty())
        q.pop();
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : g[u]) {
            if (find(v) == find(u) || vis[v] == 2)
                continue;
            if (!vis[v]) {
                vis[v] = 2;
                pre[v] = u;
                if (!cp[v]) {
                    for (int now = v, las; now; now = las)
                        las = cp[pre[now]], cp[now] = pre[now],
                        cp[pre[now]] = now;
                    return 1;
                }
                vis[cp[v]] = 1, q.push(cp[v]);
            } else {
                int w = lca(u, v);
                blossom(u, v, w);
                blossom(v, u, w);
            }
        }
    }
    return 0;
}
int main() {
    int ans = 0;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; i++)
        if (!cp[i])
            ans += work(i);
    cout << ans << endl;
    for (int i = 1; i <= n; i++)
        cout << cp[i] << " ";
}
