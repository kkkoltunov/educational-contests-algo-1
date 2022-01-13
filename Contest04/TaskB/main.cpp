#include <iostream>
#include <string>

void printTable(std::string *table, const int &count_strings) {
    for (int i = 0; i < (count_strings * 2) + 1; i++) {
        std::cout << table[i];

        if (i + 1 != (count_strings * 2) + 1) {
            std::cout << '\n';
        }
    }
}

void createTable(int **array, const int &count_strings) {
    int len_arr = (count_strings * 2) + 1;
    std::string *table;
    table = new std::string[len_arr];

    for (unsigned int i = 0; i < count_strings; ++i) {
        bool first_passage = true;
        for (unsigned int j = i * 2; j <= (i * 2) + 2; ++j) {
            int iterator_for_array = 1;
            int length_of_string = 1;

            for (unsigned int k = 0; k <= array[i][0]; ++k) {
                length_of_string += array[i][k];
            }

            char current_char_first;
            char current_char_second;

            if (j != i * 2 || j == 0) {
                table[j] = std::string(length_of_string, ' ');
            }

            if (length_of_string > table[j].length()) {
                std::string tmp = table[j];
                table[j] = std::string(length_of_string, ' ');


                for (int k = 0; k < tmp.length(); k++) {
                    table[j][k] = tmp[k];
                }
            }

            if (j % 2 == 0) {
                current_char_first = '+';
                current_char_second = '-';
            } else {
                current_char_first = '|';
                current_char_second = ' ';
            }

            table[j][0] = current_char_first;

            int count_to_second_char = array[i][iterator_for_array++];

            for (unsigned int k = 1; k < length_of_string - 1; ++k) {
                if (!first_passage || j == 0) {
                    table[j][k] = current_char_second;
                } else if (table[j][k] == ' ') {
                    table[j][k] = current_char_second;
                }
                --count_to_second_char;

                if (count_to_second_char == 0) {
                    table[j][++k] = current_char_first;
                    count_to_second_char = array[i][iterator_for_array++];
                }
            }

            if (!first_passage || j == 0) {
                table[j][length_of_string] = current_char_first;
            }
            first_passage = false;
        }
    }

    printTable(table, count_strings);
}

int main() {
    int count_strings;
    std::cin >> count_strings;

    int *array[count_strings];

    for (unsigned int i = 0; i < count_strings; ++i) {
        int count_cells;
        std::cin >> count_cells;

        array[i] = new int[count_cells + 1];
        array[i][0] = count_cells;
        for (unsigned int j = 1; j <= count_cells; ++j) {
            std::cin >> array[i][j];
        }
    }

    createTable(array, count_strings);
}
