#include <iostream>
#include <vector>

void printArray(const std::vector<std::vector<int64_t>> &arr,
                const int &count_lines_in_array, const int &count_columns_in_array) {
    for (unsigned int i = 0; i < count_lines_in_array; i++) {
        for (unsigned int j = 0; j < count_columns_in_array; j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int count_lines_in_array;
    int count_columns_in_array;
    std::cin >> count_lines_in_array >> count_columns_in_array;
    std::vector<std::vector<int64_t>> arr;
    arr.push_back(std::vector<int64_t>(count_columns_in_array, 1));

    for (unsigned int i = 1; i < count_lines_in_array; ++i) {
        arr.push_back(std::vector<int64_t>(count_columns_in_array, 1));
        for (unsigned int j = 1; j < count_columns_in_array; ++j) {
            arr[i][j] = arr[i - 1][j] + arr[i][j - 1];
        }
    }

    printArray(arr, count_lines_in_array, count_columns_in_array);
}
