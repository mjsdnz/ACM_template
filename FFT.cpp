#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int G = 3; // 原根

long long modpow(long long a, long long e) {
	long long r = 1;
	while (e) {
		if (e & 1) r = r * a % MOD;
		a = a * a % MOD;
		e >>= 1;
	}
	return r;
}

void ntt(vector<int>& a, bool invert) {
	int n = a.size();
	
	// 位逆序置换
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j & bit; bit >>= 1) j ^= bit;
		j ^= bit;
		if (i < j) swap(a[i], a[j]);
	}
	
	// 蝶形合并
	for (int len = 2; len <= n; len <<= 1) {
		int wlen = modpow(G, (MOD - 1) / len);
		if (invert) wlen = modpow(wlen, MOD - 2);
		
		for (int i = 0; i < n; i += len) {
			long long w = 1;
			for (int j = 0; j < len / 2; j++) {
				int u = a[i + j];
				int v = (int)(a[i + j + len / 2] * w % MOD);
				a[i + j] = (u + v) % MOD;
				a[i + j + len / 2] = (u - v + MOD) % MOD;
				w = w * wlen % MOD;
			}
		}
	}
	
	if (invert) {
		int inv_n = modpow(n, MOD - 2);
		for (int& x : a) x = (int)(1LL * x * inv_n % MOD);
	}
}

// 封装卷积函数
vector<int> convolution(const vector<int>& a, const vector<int>& b) {
	vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	int n = 1;
	int need = a.size() + b.size() - 1;
	while (n < need) n <<= 1;
	
	fa.resize(n);
	fb.resize(n);
	
	ntt(fa, false);
	ntt(fb, false);
	for (int i = 0; i < n; i++) fa[i] = (int)(1LL * fa[i] * fb[i] % MOD);
	ntt(fa, true);
	
	fa.resize(need);
	return fa;
}
