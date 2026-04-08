#include <bits/stdc++.h>
using namespace std;
// 因为树状数组没有明确的树形结构，所以就不写类了。
const int N = 2e6 + 10;
int n, m;
int tree[N];
#define lowbit(x) ((-x) & x)
void add(int x, int val) {
    while (x <= n)
        tree[x] += val, x += lowbit(x);
}
int query(int x) {
    int ans = 0;
    while (x != 0) {
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}
int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int aa;
        cin >> aa;
        add(i, aa);
    }
    while (m--) {
        int opt, a, b;
        cin >> opt >> a >> b;
        if (opt == 1)
            add(a, b);
        else
            cout << query(b) - query(a - 1) << endl;
    }
}
