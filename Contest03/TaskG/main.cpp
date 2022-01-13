#include <iostream>
#include <vector>

int main() {
    int count_lines_in_array;
    int count_columns_in_array;
    std::cin >> count_lines_in_array >> count_columns_in_array;

    std::vector<std::vector<int>> arr;

    for (unsigned int i = 0; i < count_lines_in_array; i++) {
        arr.push_back(std::vector<int>(count_columns_in_array));

        for (unsigned int second_iterator = 0; second_iterator < count_columns_in_array; second_iterator++) {
            std::cin >> arr[i][second_iterator];
        }
    }

    std::cout << count_columns_in_array << " " << count_lines_in_array << std::endl;

    for (unsigned int i = 0; i < count_columns_in_array; ++i) {
        for (unsigned int j = count_lines_in_array - 1; j != -1; --j) {
            std::cout << arr[j][i] << " ";
        }
        std::cout << std::endl;
    }
}
