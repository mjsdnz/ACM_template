#include <bits/stdc++.h>
using namespace std;
namespace LCA {
const int N = 5e5 + 10;
vector<int> g[N];
int dep[N];
int fa[N];
int top[N];
int son[N];
int siz[N];
void dfs1(int u, int fa) {
    siz[u] = 1;
    son[u] = 0;
    LCA::fa[u] = fa;
    dep[u] = dep[fa] + 1;
    for (auto v : g[u]) {
        if (v == fa)
            continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]])
            son[u] = v; // 记录重儿子
    }
}
void dfs2(int u, int fa, int top) {
    LCA::top[u] = top;
    if (!son[u])
        return;
    dfs2(son[u], u, top); // 先递归重链
    for (auto v : g[u]) {
        if (v == fa || v == son[u])
            continue;
        dfs2(v, u, v);
    }
}
int lca(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] >= dep[top[y]])
            x = fa[top[x]];
        else
            y = fa[top[y]];
    }
    return dep[x] < dep[y] ? x : y;
}
} // namespace LCA
int n, m, s;
int main() {
    cin >> n >> m >> s;
    using namespace LCA;
    for (int i = 1; i <= n - 1; i++) {
        int aa, bb;
        cin >> aa >> bb;
        g[aa].push_back(bb);
        g[bb].push_back(aa);
    }
    dfs1(s, 0);
    dfs2(s, 0, s);
    while (m--) {
        int x, y;
        cin >> x >> y;
        cout << lca(x, y) << endl;
    }
}
