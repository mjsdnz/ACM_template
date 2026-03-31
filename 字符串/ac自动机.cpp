#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;

int tr[N][26];   // Trie 树
int fail[N];     // 失配指针
int cnt[N];      // 结尾标记（可以统计出现次数）
int idx = 0;     // 当前节点编号（0 是根）

// 插入字符串
void insert(string s) {
    int p = 0;
    for (int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        if (!tr[p][c]) tr[p][c] = ++idx;
        p = tr[p][c];
    }
    cnt[p]++; // 标记结尾
}

// 构建 fail 指针（BFS）
void build() {
    queue<int> q;

    // 初始化第一层
    for (int i = 0; i < 26; i++) {
        if (tr[0][i]) {
            fail[tr[0][i]] = 0;
            q.push(tr[0][i]);
        }
    }

    // BFS 构建
    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int i = 0; i < 26; i++) {
            int v = tr[u][i];
            if (v) {
                fail[v] = tr[fail[u]][i];
                q.push(v);
            } else {
                // 关键优化：自动补全跳转
                tr[u][i] = tr[fail[u]][i];
            }
        }
    }
}

// 查询（统计匹配次数）
int query(string s) {
    int p = 0, res = 0;

    for (int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        p = tr[p][c];
        int t = p;
        while (t && cnt[t] != -1) {
            res += cnt[t];
            cnt[t] = -1; // 防止重复统计
            t = fail[t];
        }
    }
    return res;
}

int main() {
    int n;
    cin >> n;

    while (n--) {
        string s;
        cin >> s;
        insert(s);
    }
    build();
    string text;
    cin >> text;
    cout << query(text) << endl;
    return 0;
}
/*用于多模式串匹配 
返匹配成功的次数*/ 
