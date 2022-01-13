#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> findBulletin(int m) {
    std::vector<std::string> arr(m);

    for (auto &element: arr) {
        std::cin >> element;
    }

    return arr;
}

bool isStringTrue(std::string string) {
    int counter = 0;

    for (unsigned int i = 0; i < string.size(); i++) {
        if (string[i] == '+') {
            counter++;
        }

        if (counter > 1) {
            return false;
        }
    }

    return true;
}

void printResults(std::vector<int> arr_int, double counter_voices) {
    for (unsigned int i = 0; i < arr_int.size(); i++) {
        if (arr_int[i] / counter_voices >= 0.07) {
            std::cout << i + 1 << " ";
        }
    }
}

void counterVoices(std::vector<std::string> arr, int n) {
    std::vector<int> arr_int(n);

    double counter_voices = 0;

    for (unsigned int i = 0; i < arr.size(); i++) {
        if (isStringTrue(arr[i])) {
            for (unsigned int j = 0; j < arr[i].size(); j++) {
                if (arr[i][j] == '+') {
                    arr_int[j]++;
                    counter_voices++;
                    break;
                }
            }
        }
    }

    printResults(arr_int, counter_voices);
}

int main() {
    int n, m;

    std::cin >> n >> m;

    std::vector<std::string> arr = findBulletin(m);

    counterVoices(arr, n);
}

