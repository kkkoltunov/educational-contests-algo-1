#include <iostream>
#include <string>

void Decryption(const std::string &input) {
    int counter = input.length() - 1;
    int length = input.length();

    if (input.length() % 2 == 1) {
        counter--;
    } else {
        counter -= 2;
    }

    std::cout << input[0];

    for (int i = 1; i < length / 2; ++i) {
        std::cout << input[i * 2];
    }

    while (counter > 0) {
        std::cout << input[counter];
        counter -= 2;
    }
}

int main() {
    std::string input;
    std::cin >> input;

    Decryption(input);
    return 0;
}

