#include <iostream>
#include <vector>

bool isArrayMatchesInput(std::vector<int> &arr_data) {
    for (unsigned int i = 0; i < arr_data.size(); i++) {
        if (arr_data[i] != 0) {
            return 0;
        }
    }

    return 1;
}

int findInputArray(std::vector<int> &arr_data) {
    int counter = 0;

    while (true) {
        for (unsigned int i = 0; i < arr_data.size(); i++) {
            if (arr_data[i] % 2 != 0) {
                if (arr_data[i] < 0) {
                    arr_data[i]++;
                    counter++;
                }

                if (arr_data[i] > 0) {
                    arr_data[i]--;
                    counter++;
                }
            }
        }

        for (unsigned int i = 0; i < arr_data.size(); i++) {
            arr_data[i] /= 2;
        }

        if (isArrayMatchesInput(arr_data)) {
            break;
        }

        counter++;
    }

    return counter;
}

int main() {
    unsigned int array_length;
    std::cin >> array_length;

    std::vector<int> arr_data(array_length);

    for (unsigned int i = 0; i < array_length; ++i) {
        std::cin >> arr_data[i];
    }

    std::cout << findInputArray(arr_data);
}