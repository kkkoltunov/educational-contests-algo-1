#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> findDecomposeArray(const std::vector<int> &arr_data) {
    if (arr_data.size() <= 2) {
        return arr_data;
    }

    int count_blocks_in_array = static_cast<int>(std::ceil(std::sqrt(arr_data.size())));

    std::vector<int> arr_decompose(count_blocks_in_array);

    for (unsigned int i = 0, j = 0; i < arr_data.size(); i++) {
        if (i != 0 && i % count_blocks_in_array == 0) {
            j++;
        }

        if (arr_data[i] == 0) {
            arr_decompose[j]++;
        }
    }

    return arr_decompose;
}

void findCountNulls(const std::vector<int> &arr_input, const std::vector<int> &arr_decompose) {
    unsigned int count_request_for_find_nulls;
    std::cin >> count_request_for_find_nulls;

    const int size_decompose_array = arr_decompose.size();

    for (unsigned int i = 0; i < count_request_for_find_nulls; i++) {
        int counter = 0;
        int left_border;
        int right_border;
        std::cin >> left_border >> right_border;

        left_border--;
        right_border--;

        do {
            if (left_border % size_decompose_array == 0) {
                if (left_border + size_decompose_array - 1 <= right_border) {
                    counter += arr_decompose[left_border / size_decompose_array];
                    left_border += size_decompose_array;
                } else if (arr_input[left_border++] == 0) {
                    counter++;
                }
            } else if (arr_input[left_border++] == 0) {
                counter++;
            }
        } while (left_border <= right_border);

        std::cout << counter << " ";
    }
}

int main() {
    // https://stackoverflow.com/questions/31162367/
    // significance-of-ios-basesync-with-stdiofalse-cin-tienull
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int count_numbers_in_array;
    std::cin >> count_numbers_in_array;

    std::vector<int> arr_data(count_numbers_in_array);

    for (unsigned int i = 0; i < count_numbers_in_array; i++) {
        std::cin >> arr_data[i];
    }

    findCountNulls(arr_data, findDecomposeArray(arr_data));
}
