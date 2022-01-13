#include <iostream>
#include <stack>
#include <algorithm>

// https://e-maxx.ru/algo/stacks_for_minima#2.
void findMinimums(const int &array_lenght, const int &count_of_find_elements) {
    std::stack<std::pair<int, int>> stack_input;
    std::stack<std::pair<int, int>> stack_output;

    for (unsigned int i = 0; i < array_lenght; ++i) {
        int minimum;
        int input;
        std::cin >> input;

        if (stack_input.empty()) {
            minimum = input;
        } else {
            minimum = std::min(input, stack_input.top().second);
        }

        stack_input.push(std::make_pair(input, minimum));

        if (i >= count_of_find_elements - 1) {
            if (stack_input.empty() || stack_output.empty()) {
                if (stack_input.empty()) {
                    std::cout << stack_output.top().second << " ";
                } else {
                    std::cout << stack_input.top().second << " ";
                }
            } else {
                std::cout << std::min(stack_input.top().second, stack_output.top().second) << " ";
            }
            if (stack_output.empty()) {
                while (!stack_input.empty()) {
                    int element = stack_input.top().first;
                    stack_input.pop();

                    if (stack_output.empty()) {
                        minimum = element;
                    } else {
                        minimum = std::min(element, stack_output.top().second);
                    }

                    stack_output.push(std::make_pair(element, minimum));
                }
            }
            stack_output.pop();
        }
    }
}

int main() {
    // https://stackoverflow.com/questions/31162367/
    // significance-of-ios-basesync-with-stdiofalse-cin-tienull.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int array_length;
    unsigned int count_of_find_elements;
    std::cin >> array_length >> count_of_find_elements;

    findMinimums(array_length, count_of_find_elements);
}