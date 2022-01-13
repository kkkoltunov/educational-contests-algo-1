#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> printShifts(const std::vector<int> &arr, const int &shift,
                                     std::vector<std::string> already_output) {
    std::string output;

    for (unsigned int i = 0; i < arr.size(); ++i) {
        if (i + 1 != arr.size()) {
            output += std::to_string(arr[(i + (arr.size() - shift)) % arr.size()]) + " ";
        }
    }

    for (unsigned int i = 0; i < already_output.size(); ++i) {
        if (output == already_output[i]) {
            return already_output;
        }
    }

    already_output.push_back(output);

    std::cout << output;
    std::cout << arr[((arr.size() - 1) + (arr.size() - shift)) % arr.size()];
    std::cout << "; " << shift << std::endl;

    return already_output;
}

std::vector<int> findDistanceBetweenShifts(const std::vector<int> &arr, std::vector<int> arr_shifts,
                                           const int &shift, int *max) {
    int counter = 0;

    for (unsigned int i = 0; i < arr.size(); ++i) {
        if (arr[i] != arr[(i + (arr.size() - shift)) % arr.size()]) {
            counter++;
        }
    }

    if (counter > *max) {
        *max = counter;
        arr_shifts.clear();
        arr_shifts.push_back(shift);
    } else if (counter == *max) {
        arr_shifts.push_back(shift);
    }

    return arr_shifts;
}

void findShifts(const std::vector<int> &arr) {
    std::vector<int> arr_shifts;
    std::vector<std::string> already_output;

    int max = -1;

    for (unsigned int i = 0; i < arr.size(); ++i) {
        arr_shifts = findDistanceBetweenShifts(arr, arr_shifts, i, &max);
    }

    std::cout << max << std::endl;

    for (int &arr_shift: arr_shifts) {
        already_output = printShifts(arr, arr_shift, already_output);
    }
}

int main() {
    // https://stackoverflow.com/questions/31162367/
    // significance-of-ios-basesync-with-stdiofalse-cin-tienull
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int array_length;
    std::cin >> array_length;

    std::vector<int> arr_data(array_length);

    for (unsigned int i = 0; i < array_length; ++i) {
        std::cin >> arr_data[i];
    }

    if (array_length == 1) {
        std::cout << 0 << std::endl;
        std::cout << arr_data[0] << "; " << 0;
        return 0;
    }

    findShifts(arr_data);
}
