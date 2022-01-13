#include <iostream>
#include <string>

void findChildren(const std::string &schyactalochka, const std::string &names) {
    int count_words = 1;
    for (char i : schyactalochka) {
        if (i == ' ') {
            ++count_words;
        }
    }

    int count_names = 1;
    for (char i : names) {
        if (i == ' ') {
            ++count_names;
        }
    }

    int count_backspaces = (count_words - 1) % count_names;
    int counter_backspaces = 0;

    for (unsigned int i = 0; i < names.length(); ++i) {
        if (names[i] == ' ') {
            ++counter_backspaces;
        }

        if (counter_backspaces == count_backspaces) {
            while (true) {
                if (names[i] == ' ') {
                    ++i;
                }

                std::cout << names[i++];

                if (i >= names.length()) {
                    break;
                }

                if (names[i] == ' ') {
                    break;
                }
            }
            break;
        }
    }
}

int main() {
    std::string schyactalochka;
    std::getline(std::cin, schyactalochka);
    std::string names;
    std::getline(std::cin, names);

    findChildren(schyactalochka, names);

    return 0;
}

