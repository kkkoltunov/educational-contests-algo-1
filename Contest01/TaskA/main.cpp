#include <iostream>

using namespace std;

int main() {
    float average = 0;
    int count = 0;
    float input;
    cin >> input;

    while (input != 0) {
        average += input;
        count++;
        cin >> input;
    }

    average /= count;

    cout.precision(5);

    cout << average;
}