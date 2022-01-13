#include <iostream>

bool isCrypto(std::string input) {
    bool flag_lowercase_letter = false;
    bool flag_capital_letter = false;
    bool flag_figure = false;

    if (input.length() < 8) {
        return false;
    }

    for (int i = 0; i < input.length(); i++) {
        if (input[i] >= 'a' && input[i] <= 'z') {
            flag_lowercase_letter = true;
        }

        if (input[i] >= 'A' && input[i] <= 'Z') {
            flag_capital_letter = true;
        }

        if (input[i] >= '0' && input[i] <= '9') {
            flag_figure = true;
        }

        if (flag_capital_letter && flag_figure && flag_lowercase_letter) {
            return true;
        }
    }

    return false;
}

int main() {
    std::string input;

    std::cin >> input;

    if (isCrypto(input)) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
}