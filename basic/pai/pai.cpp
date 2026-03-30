#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
using namespace std;
const int time_limit = 1000;
bool linux_work() {
    system("./data > data.in");
    system("./baoli < data.in > baoli.out");
    double b = clock();
    system("./std < data.in > std.out");
    double e = clock();
    double t = e - b;
    if (system("diff baoli.out std.out")) {
        puts("WA");
        return 0;
    } else if (t > time_limit) {
        printf("TLE ,use %lf seconds\n", t / 1000.0);
    } else
        puts("AC");
    return 1;
}

bool windows_work() {
    system("data.exe > data.in");
    system("baoli.exe < data.in > baoli.out");
    double b = clock();
    system("std.exe < data.in > std.out");
    double e = clock();
    double t = e - b;
    if (system("fc baoli.out std.out")) {
        puts("WA");
        return 0;
    } else if (t > time_limit) {
        printf("TLE ,use %lf seconds\n", t / 1000.0);
    } else
        puts("AC");
    return 1;
}

#if defined(_WIN32)
#define work() windows_work()
#elif defined(__linux__)
#define work() linux_work()
#endif

int main() {
    int T = 1000;
    while (T--) {
        if (!work())
            return 0;
    }
}
