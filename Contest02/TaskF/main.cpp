#include <iostream>

int gcd(const int &first_number, const int &second_number, int &count_function_calls) {
    count_function_calls++;

    if (second_number != 0) {
        return gcd(second_number, first_number % second_number, count_function_calls);
    }

    return first_number;
}

void findGcd(const int &count_numbers_in_sequence, int &count_function_calls) {
    int result = 0;

    for (unsigned int i = 0; i < count_numbers_in_sequence - 1; i++) {
        double first_number;

        if (i == 0) {
            std::cin >> first_number;

            if (int(first_number) != first_number) {
                std::cout << "Sequence has float values!";
                return;
            }
        }

        double second_number;

        std::cin >> second_number;

        if (int(second_number) != second_number) {
            std::cout << "Sequence has float values!";
            return;
        }

        if (i == 0) {
            result = gcd(static_cast<int>(second_number), static_cast<int>(first_number), count_function_calls);
        } else {
            result = gcd(static_cast<int>(second_number), result, count_function_calls);
        }

    }

    std::cout << result << " " << count_function_calls;
}

int main() {
    int count_function_calls = 0;
    int count_numbers_in_sequence;
    double number;

    std::cin >> count_numbers_in_sequence;

    if (count_numbers_in_sequence == 1) {
        std::cin >> number;

        if (int(number) != number) {
            std::cout << "Sequence has float values!";
            return 0;
        } else {
            std::cout << number << " " << 0;
            return 0;
        }
    }

    findGcd(count_numbers_in_sequence, count_function_calls);

    return 0;
}
