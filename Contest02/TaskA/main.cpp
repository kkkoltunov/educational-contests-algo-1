#include <iostream>

bool isPalindrome(std::string str) {
    std::string consonant_letters;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] != 'a' && str[i] <= 'u' && str[i] != 'i' && str[i] != 'o' && str[i] != 'e' && str[i] != 'y') {
            consonant_letters += str[i];
        }
    }

    int left_board = 0;
    int right_board = consonant_letters.length() - 1;

    while ((left_board != right_board && consonant_letters.length() % 2 == 1) ||
           (left_board - 1 != right_board && consonant_letters.length() % 2 == 0)) {
        if (consonant_letters[left_board++] != consonant_letters[right_board--]) {
            return false;
        }
    }

    return true;
}

int main() {
    std::string str;

    std::cin >> str;

    if (isPalindrome(str)) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
}