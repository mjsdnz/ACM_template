#include <bits/stdc++.h>
#define int long long
int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int gcd = exgcd(b, a % b, x, y);
    int now = x;
    x = y;
    y = now - a / b * y;
    return gcd;
}
using namespace std;
void work() {
    int a, b, c, d, x, y;
    cin >> a >> b >> c;
    d = exgcd(a, b, x, y);
    if (c % d != 0)
        puts("-1");
    else {
        x *= c / d, y *= c / d;
        int p = b / d, q = a / d, k;
        if (x < 0)
            k = ceil((1.0 - x) / p), x += p * k, y -= q * k;
        else if (x >= 0)
            k = (x - 1) / p, x -= p * k, y += q * k;
        if (y > 0) {
            cout << (y - 1) / q + 1 << " ";
            cout << x << " ";
            cout << (y - 1) % q + 1 << " ";
            cout << x + (y - 1) / q * p << " ";
            cout << y << " ";
        } else {
            cout << x << " ";
            cout << y + q * (int)ceil((1.0 - y) / q) << " ";
        }
        puts("");
    }
}

signed main() {
    int T;
    cin >> T;
    while (T--) {
        work();
    }
}
