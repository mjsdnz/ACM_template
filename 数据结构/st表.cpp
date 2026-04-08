#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
const int N = 1e5 + 10;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}
int n, m;
int lg[N];
int f[N][32];
int main() {
    n = read(), m = read();
    lg[1] = 0;
    for (int i = 1; i <= n; i++) {
        if (i >= 2)
            lg[i] = lg[i >> 1] + 1;
        f[i][0] = read();
    }
    for (int i = 1; i <= lg[n]; i++)
        for (int j = 1; j <= n - (1 << i) + 1; j++)
            f[j][i] = max(f[j][i - 1], f[j + (1 << (i - 1))][i - 1]);
    while (m--) {
        int a, b;
        a = read(), b = read();
        int k = lg[b - a + 1];
        printf("%d\n", max(f[a][k], f[b - (1 << k) + 1][k]));
    }
}
