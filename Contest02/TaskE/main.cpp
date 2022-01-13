#include <iostream>

std::string concatenation(std::string str_first, std::string str_second, long count_iteration) {
    std::string current_str;

    for (unsigned int i = 0; i < count_iteration; i++) {
        current_str = str_first + str_second;
        str_first = str_second;
        str_second = current_str;
    }

    return current_str;
}

int main() {
    std::string str_first, str_second;
    long count_iteration, position;

    std::cin >> str_first >> str_second;
    std::cin >> count_iteration >> position;

    std::string result_str = concatenation(str_first, str_second, count_iteration);

    std::cout << result_str[position - 1];
}