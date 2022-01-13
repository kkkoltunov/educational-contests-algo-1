#include <iostream>

int64_t gcd(const int64_t &first_number, const int64_t &second_number) {
    if (second_number != 0) {
        return gcd(second_number, first_number % second_number);
    }

    return first_number;
}

int64_t lcm(const int64_t &gcd, const int64_t &first_number, const int64_t &second_number) {
    return (first_number * second_number) / gcd;
}

void findLcm(const int &count_numbers_in_sequence) {
    int64_t result = 0;

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
            result = lcm(gcd(static_cast<int64_t>(second_number), static_cast<int64_t>(first_number)),
                         static_cast<int64_t>(second_number), static_cast<int64_t>(first_number));
        } else {
            result = lcm(gcd(static_cast<int64_t>(second_number), result), static_cast<int64_t>(second_number), result);
        }
    }

    std::cout << result;
}

int main() {
    int count_numbers_in_sequence;
    double number;

    std::cin >> count_numbers_in_sequence;

    if (count_numbers_in_sequence == 1) {
        std::cin >> number;

        if (int(number) != number) {
            std::cout << "Sequence has float values!";
            return 0;
        } else {
            std::cout << number;
            return 0;
        }
    }

    findLcm(count_numbers_in_sequence);

    return 0;
}
