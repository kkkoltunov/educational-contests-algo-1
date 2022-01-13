#include <iostream>
#include <string>

using namespace std;

int counter(string k) {
    int left_counter = 0;
    int right_counter = k.length() - 1;

    int count = 0;

    if (k.length() == 1) {
        return 1;
    }

    if (k.length() % 2 == 0) {
        while (left_counter - 1 != right_counter) {
            if (k[left_counter++] == k[right_counter--]) {
                count++;
            } else {
                return 0;
            }
        }

        if (count == k.length() / 2) {
            return 1;
        }
    }

    if (k.length() % 2 == 1) {
        while (left_counter != right_counter) {
            if (k[left_counter++] == k[right_counter--]) {
                count++;
            } else {
                return 0;
            }
        }

        if (count == k.length() / 2) {
            return 1;
        }
    }

    return 0;
}

int main() {
    int a = 15;
    string str = to_string(a);

    int k;
    cin >> k;

    int count = 0;

    for (int i = 1; i <= k; i++) {
        count += counter(to_string(i));
    }

    cout << count;
}