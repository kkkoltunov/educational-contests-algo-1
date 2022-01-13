#include <iostream>
#include <string>

void FindDifferences(const std::string& firstLine, const std::string& secondLine) {
    int arrayCharsFirstLine[26];
    int arrayCharsSecondLine[26];

    for (unsigned int i = 0; i < 26; ++i) {
        arrayCharsFirstLine[i] = 0;
        arrayCharsSecondLine[i] = 0;
    }

    for (unsigned int i = 0; i < firstLine.length(); ++i) {
        if (firstLine[i] != ' ') {
            arrayCharsFirstLine[static_cast<int>(firstLine[i] - 'a')] = 1;
        }
    }

    for (unsigned int i = 0; i < secondLine.length(); ++i) {
        if (secondLine[i] != ' ') {
            arrayCharsSecondLine[static_cast<int>(secondLine[i] - 'a')] = 1;
        }
    }

    bool emptyString = true;

    for (unsigned int i = 0; i < 26; ++i) {
        if ((arrayCharsFirstLine[i] ^ arrayCharsSecondLine[i]) == 1) {
            std::cout << static_cast<char>(97 + i) << " ";
            emptyString = false;
        }
    }

    if (emptyString) {
        std::cout << "NONE";
    }
}

int main() {
    std::string firstLine;
    std::string secondLine;
    std::getline(std::cin, firstLine);
    std::getline(std::cin, secondLine);

    FindDifferences(firstLine, secondLine);
    return 0;
}
