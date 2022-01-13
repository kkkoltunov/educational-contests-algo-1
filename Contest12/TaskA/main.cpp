#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>

int priorityOperation(const std::string &check_string) {
    if (check_string == "*" || check_string == "/") {
        return 2;
    }
    if (check_string == "+" || check_string == "-") {
        return 1;
    } else {
        return 0;
    }
}

void findPostfixNote(std::vector<std::string> *infix_sequence_vector,
                     std::vector<std::string> *postfix_sequence) {
    std::stack<std::string> stack;
    for (size_t index = 0; index < infix_sequence_vector->size(); ++index) {
        if (infix_sequence_vector->operator[](index)[0] >= '0' &&
            infix_sequence_vector->operator[](index)[0] <= '9') {
            postfix_sequence->push_back(infix_sequence_vector->operator[](index));
        } else if (infix_sequence_vector->operator[](index)[0] == '(') {
            stack.push(infix_sequence_vector->operator[](index));
        } else if (infix_sequence_vector->operator[](index)[0] == ')') {
            while (!stack.empty() && stack.top() != "(") {
                postfix_sequence->push_back(stack.top());
                stack.pop();
            }
            stack.pop();
        } else if (infix_sequence_vector->operator[](index)[0] == '+' ||
                   infix_sequence_vector->operator[](index)[0] == '*' ||
                   infix_sequence_vector->operator[](index)[0] == '-' ||
                   infix_sequence_vector->operator[](index)[0] == '/') {
            while (!stack.empty() &&
                   priorityOperation(stack.top()) >=
                       priorityOperation(infix_sequence_vector->operator[](index))) {
                postfix_sequence->push_back(stack.top());
                stack.pop();
            }
            stack.push(infix_sequence_vector->operator[](index));
        }
    }

    int size = stack.size();
    for (size_t i = 0; i < size; ++i) {
        postfix_sequence->push_back(stack.top());
        stack.pop();
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string infix_sequence;
    std::getline(std::cin, infix_sequence);
    std::istringstream parser(infix_sequence);
    infix_sequence += " ";

    std::vector<std::string> infix_sequence_vector;
    while (parser) {
        std::string substring;
        parser >> substring;
        infix_sequence_vector.push_back(substring);
    }

    std::vector<std::string> postfix_sequence;
    findPostfixNote(&infix_sequence_vector, &postfix_sequence);

    for (auto &element : postfix_sequence) {
        std::cout << element << " ";
    }

    return 0;
}
