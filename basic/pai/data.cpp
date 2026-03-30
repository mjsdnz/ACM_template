#include <bits/stdc++.h>
#include <sys/timeb.h>
using namespace std;
int main() {
    timeb T;
    ftime(&T);
    srand(T.millitm); // 获得毫秒
    int a = rand() % 100000;
    int b = rand() % 100000;
    printf("%d %d\n", a, b);
}
