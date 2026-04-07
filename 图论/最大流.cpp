#include <queue>
#include <vector>
using namespace std;
struct Dinic {
    struct Edge {
        int to;
        long long cap;
        int rev;
    };
    int n;
    vector<vector<Edge>> g;
    vector<int> level, it;
    Dinic(int n) : n(n), g(n), level(n), it(n) {}
    void add_edge(int u, int v, int c) {
        Edge a{v, c, (int)g[v].size()};
        Edge b{u, 0, (int)g[u].size()};
        g[u].push_back(a);
        g[v].push_back(b);
    }
    bool bfs(int s, int t) {
        queue<int> q;
        q.push(s);
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &e : g[v]) {
                if (level[e.to] != -1 or e.cap <= 0)
                    continue;
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
        return level[t] >= 0;
    }
    long long dfs(int v, int t, long long f) {
        if (v == t)
            return f;
        for (int &i = it[v]; i < (int)g[v].size(); i++) {
            Edge &e = g[v][i];
            if (e.cap <= 0)
                continue;
            if (level[e.to] != level[v] + 1)
                continue;
            long long pushed = dfs(e.to, t, min(f, e.cap));
            if (pushed > 0) {
                e.cap -= pushed;
                g[e.to][e.rev].cap += pushed;
                return pushed;
            }
        }
        return 0;
    }
    long long Maxflow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (true) {
                long long pushed;
                pushed = dfs(s, t, MAXCAP);
                if (!pushed)
                    break;
                flow += pushed;
            }
        }
        return flow;
    }
};
