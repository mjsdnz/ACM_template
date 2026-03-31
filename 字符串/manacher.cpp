#include <bits/stdc++.h>
using namespace std;

int m[23000005];
int manacher(const char s[]) {
	int ans = 0;
    int n = strlen(s);
    static char t[24000005];
    int len = 0;
    t[len++] = '^';
    t[len++] = '#';
    for (int i = 0; i < n; i++) {
        t[len++] = s[i];
        t[len++] = '#';
    }
    t[len++] = '$';
    t[len] = '\0';

    int center = 0, right = 0;
    ans = 0;

    for (int i = 1; i < len - 1; i++) {
        int mirror = 2 * center - i;
        m[i] = (i < right) ? min(m[mirror], right - i) : 0;

        while (t[i + m[i] + 1] == t[i - m[i] - 1]) m[i]++;

        ans = max(ans, m[i]);

        if (i + m[i] > right) {
            center = i;
            right = i + m[i];
        }
    }
    return ans;
}
//用于找出最大回文子序列长度 

