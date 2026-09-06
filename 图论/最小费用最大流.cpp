#include <bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 0x3f3f3f3f;
const int N = 5e3 + 10;
const int M = 1e5 + 10;
int head[N];
int cnt = 1;
int now[N];
int s, t, n, m;
struct edge
{
    int u, v, c, val, nxt;
    edge(int u = 0, int v = 0, int c = 0, int val = 0, int nxt = 0) : u(u), v(v), c(c), val(val), nxt(nxt) {}
} e[M];
void ADD(int u, int v, int c, int val)
{
    cnt++;
    e[cnt] = edge(u, v, c, val, head[u]);
    head[u] = cnt;
}
void add_edge(int u, int v, int c, int val)
{
    ADD(u, v, c, val);
    ADD(v, u, 0, -val);
}
int dis[N];
bool vis[N];
int pre[N];
int flow[N];
bool spfa(int s, int t)
{
    for (int i = 1; i <= n; i++)
        dis[i] = inf;
    memset(flow, 0, sizeof flow);
    memset(vis, 0, sizeof vis);
    memcpy(now, head, sizeof head);
    dis[s] = 0;
    vis[s] = 1;
    flow[s] = inf;
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        vis[u] = 0;
        q.pop();
        for (int i = head[u]; i; i = e[i].nxt)
        {
            int v = e[i].v;
            int c = e[i].c;
            int val = e[i].val;
            if (c && dis[v] > dis[u] + val)
            {
                dis[v] = dis[u] + val;
                flow[v] = min(c, flow[u]);
                pre[v] = i;
                if (vis[v])
                    continue;
                q.push(v);
                vis[v] = 1;
            }
        }
    }
    return flow[t] > 0;
}
int cost, maxflow;
int Dinic(int u, int t, int flow)
{
    if (u == t)
        return flow;
    vis[u] = 1;
    int nowflow = 0;
    for (int i = now[u]; i; i = e[i].nxt)
    {
        now[u] = i;
        int v = e[i].v;
        if (dis[v] == dis[u] + e[i].val && e[i].c && !vis[v])
        {
            int ff = Dinic(v, t, min(flow - nowflow, e[i].c));
            if (ff)
                cost += ff * e[i].val, e[i].c -= ff, e[i ^ 1].c += ff, nowflow += ff;
        }
    }
    vis[u] = 0;
    return nowflow;
}
void EK(int &maxflow, int &cost)
{
    maxflow = cost = 0;
    while (spfa(s, t))
    {
        int ff = flow[t];
        maxflow += ff;
        cost += ff * dis[t];
        for (int u = t; u != s; u = e[pre[u]].u)
        {
            int i = pre[u];
            e[i].c -= ff;
            e[i ^ 1].c += ff;
        }
    }
}
signed main()
{
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= m; i++)
    {
        int u, v, c, val;
        cin >> u >> v >> c >> val;
        add_edge(u, v, c, val);
    }
     while(spfa(s,t)){
        memset(vis,0,sizeof vis);
        maxflow+=Dinic(s,t,inf);
    } 
   // EK(maxflow, cost);
    cout << maxflow << " " << cost;
}
