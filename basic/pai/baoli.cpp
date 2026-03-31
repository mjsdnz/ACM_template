#include <bits/stdc++.h>
using namespace std;
int main() {
    int a, b;
    cin >> a >> b;
    int ans = 0;
    for (int i = 1; i <= a; i++)
        ans++;
    for (int i = 1; i <= b; i++)
        ans++;
    cout << ans;
}
