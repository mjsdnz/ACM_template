#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
long long phi(long long n) {
    long long result = n;
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;   //将n中所有p除去 
            result -= result / p;   //公式：*（1-1/p） 
        }
    }
    if (n > 1)
        result -= result / n;   //处理最后剩余的最大的一个质数 
    return result;
}
long long ksm(long long a, long long b, long long m) {
    long long res = 1;
    a %= m;
    while (b) {
        if (b & 1)
            res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}//快速幂 
pair<long long, bool> process_b(string b_str, long long phi_m) {
    long long res = 0;
    bool large = false;
    for (char c : b_str) {
        res = res * 10 + (c - '0');
        if (res >= phi_m) {
            large = true;
            res %= phi_m;
        }
    }
    return {res, large};
}//用字符串处理可能很大的b 
int main() {
    long long a, m;
    string b_str;
    cin >> a >> m >> b_str;
    long long phi_m = phi(m);//计算m的欧拉函数 
    pair<long long, bool> result = process_b(b_str, phi_m);
    long long b_mod = result.first;
    bool large = result.second;//处理大指数b 
    long long exp;
    if (__gcd(a, m) == 1) {
        if (large)
            exp = b_mod + phi_m;
        else
            exp = b_mod;
    } //a与m互质直接使用欧拉定理 
	else {
        if (b_mod < phi_m && !large) {
            exp = b_mod;
        } else {
            exp = b_mod + phi_m;
        }
    }//a与m不互质使用拓展欧拉定理 
    cout <<ksm(a, exp, m) << endl;
    return 0;
}
