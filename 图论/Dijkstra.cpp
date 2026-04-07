#include <bits/stdc++.h>
#include <queue>
using namespace std;
const int N = 1e5 + 10;
const int inf = 0x3f3f3f3f;
vector<pair<int, int>> g[N];
struct node {
    int v, val;
    node(int v = 0, int val = 0) : v(v), val(val) {}
    bool operator<(const node &x) const { return val > x.val; }
};
int dis[N];
bool vis[N];
int n, m, s;
void Dijkstra(int s) {
    for (int i = 1; i <= n; i++)
        dis[i] = inf;
    dis[s] = 0;
    priority_queue<node> q;
    q.push(node(s, 0));
    while (!q.empty()) {
        int u = q.top().v;
        q.pop();
        if (vis[u])
            continue;
        vis[u] = 1;
        for (auto e : g[u]) {
            int v = e.first;
            int val = e.second;
            if (dis[v] > dis[u] + val) {
                dis[v] = dis[u] + val;
                q.push(node(v, dis[v]));
            }
        }
    }
}
int main() {
    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++) {
        int u, v, val;
        cin >> u >> v >> val;
        g[u].push_back({v, val});
    }
    Dijkstra(s);
    for (int i = 1; i <= n; i++)
        cout << dis[i] << " ";
}
