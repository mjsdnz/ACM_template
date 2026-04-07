#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 100;
int n, m;
int val[N];
vector<int> g[N];
int scc[N], low[N], num[N], cnt, top, dfn, st[N], sum[N];
int aa[N], bb[N], ans[N];
void tar();
void dfs(int u);
int dfs2(int u);
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> val[i];
    for (int i = 1; i <= m; i++) {
        int aaa, bbb;
        cin >> aaa >> bbb;
        aa[i] = aaa, bb[i] = bbb;
        g[aaa].push_back(bbb);
    }
    tar();
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }
    for (int i = 1; i <= m; i++) {
        if (scc[aa[i]] != scc[bb[i]]) {
            g[scc[aa[i]]].push_back(scc[bb[i]]);
        }
    }
    int anss = 0;
    for (int i = 1; i <= n; i++) {
        if (!ans[i]) {
            anss = max(dfs2(i), anss);
        }
    }
    cout << anss << endl;
    return 0;
}
void tar() {
    for (int i = 1; i <= n; i++) {
        if (!num[i])
            dfs(i);
    }
}
void dfs(int u) {
    num[u] = low[u] = ++dfn;
    st[top++] = u;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (!num[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (!scc[v]) {
            low[u] = min(low[u], num[v]);
        }
    }
    if (num[u] == low[u]) {
        cnt++;
        while (1) {
            int v = st[--top];
            scc[v] = cnt;
            sum[cnt] += val[v];
            if (u == v)
                break;
        }
    }
    return;
}
int dfs2(int x) {
    if (ans[x])
        return ans[x];
    ans[x] = sum[x];
    int w = 0;
    for (int i = 0; i < g[x].size(); i++) {
        int v = g[x][i];
        w = max(w, dfs2(v));
    }
    ans[x] += w;
    return ans[x];
}
