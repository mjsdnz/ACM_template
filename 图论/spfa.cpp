#include <bits/stdc++.h>
#include <cstdint>
using namespace std;
const int N = 1e4 + 10;
const int inf = INT32_MAX;
vector<pair<int, int>> g[N];
int n, m, s;
int dis[N];
bool vis[N];
void spfa() {
    for (int i = 1; i <= n; i++)
        dis[i] = inf;
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = 0;
        for (auto e : g[u]) {
            int v = e.first;
            int val = e.second;
            if (dis[v] > dis[u] + val) {
                dis[v] = dis[u] + val;
                if (!vis[v]) {
                    vis[v] = 1;
                    q.push(v);
                }
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
    spfa();
    for (int i = 1; i <= n; i++)
        cout << dis[i] << " ";
}
