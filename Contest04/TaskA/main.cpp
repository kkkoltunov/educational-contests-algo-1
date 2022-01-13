#include <iostream>
#include <string>

void findString(std::string *first_number_of_sequence, const int &count_of_iterations) {
    int counter_of_iterations = 0;
    std::string new_string = *first_number_of_sequence;

    while (counter_of_iterations < count_of_iterations) {
        *first_number_of_sequence = "";

        for (unsigned int j = 0; j < new_string.length(); ++j) {
            int counter_same_figure = 1;
            char current_symbol = new_string[j];

            for (unsigned int k = j + 1; k < new_string.length(); ++k) {
                if (new_string[k] == current_symbol) {
                    ++counter_same_figure;
                } else {
                    break;
                }
            }

            *first_number_of_sequence += std::to_string(counter_same_figure) + current_symbol;
            j += counter_same_figure - 1;
        }

        new_string = *first_number_of_sequence;
        ++counter_of_iterations;
    }
}

int main() {
    std::string first_number_of_sequence;
    int count_of_iterations;

    std::cin >> first_number_of_sequence >> count_of_iterations;

    findString(&first_number_of_sequence, count_of_iterations - 1);
    std::cout << first_number_of_sequence;
}
