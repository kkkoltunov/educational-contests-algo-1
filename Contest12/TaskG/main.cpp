#include <iostream>
#include <algorithm>
#include <set>

void findMaxSequence(std::set<int> *set) {
    int maximum_sequence = 1;
    int maximum_actual = 1;

    auto pre_end = prev(set->end());
    for (auto iterator = set->begin(); iterator != pre_end; ++iterator) {
        if (*iterator + 1 == *next(iterator)) {
            ++maximum_actual;
        } else {
            maximum_actual = 1;
        }

        maximum_sequence = std::max(maximum_sequence, maximum_actual);
    }
    std::cout << maximum_sequence;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_elements;
    std::cin >> number_of_elements;
    std::set<int> set;

    for (int i = 0; i < number_of_elements; ++i) {
        int number;
        std::cin >> number;
        set.insert(number);
    }

    findMaxSequence(&set);
    return 0;
}
