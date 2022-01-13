#include <iostream>

using namespace std;

long double rec(long double a, unsigned int n) {
    if (n == 0) {
        return 1;
    }

    if (n == 1) {
        return a;
    }

    if (n % 2 == 0) {
        return rec(a * a, n / 2);
    }

    if (n % 2 == 1) {
        return a * rec(a * a, (n - 1) / 2);
    }
}

int main() {
    long double a;
    unsigned int n;
    cin >> a >> n;

    cout << rec(a, n);
}
