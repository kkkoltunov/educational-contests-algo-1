#include <iostream>
#include <string>

class Stack {
 private:
    char32_t *stack_;
    int64_t size_;

 public:
    explicit Stack(int64_t size_stack) {
        stack_ = new char32_t[size_stack];
        size_ = 0;
    }

    ~Stack() = default;

    void push(const char &data) {
        stack_[size_] = data;
        ++size_;
    }

    char32_t pop() {
        if (size_ == 0) {
            return ' ';
        }

        return stack_[size_-- - 1];
    }

    [[nodiscard]] int64_t size() const {
        return size_;
    }
};

void findBracket(const std::string &bracket_sequence) {
    Stack stack(100000);

    if (bracket_sequence.empty()) {
        std::cout << "no";
        return;
    }

    for (unsigned int i = 0; i < bracket_sequence.size(); ++i) {
        if (bracket_sequence[i] == '(' || bracket_sequence[i] == '[' || bracket_sequence[i] == '{') {
            stack.push(bracket_sequence[i]);
            continue;
        }

        char32_t current_char = stack.pop();

        if (bracket_sequence[i] == ')') {
            if (current_char != '(') {
                std::cout << "no";
                return;
            }
        } else if (bracket_sequence[i] == ']') {
            if (current_char != '[') {
                std::cout << "no";
                return;
            }
        } else if (bracket_sequence[i] == '}') {
            if (current_char != '{') {
                std::cout << "no";
                return;
            }
        }
    }

    if (stack.size() == 0) {
        std::cout << "yes";
        return;
    }

    std::cout << "no";
}

int main() {
    std::string input;
    std::getline(std::cin, input);

    findBracket(input);

    return 0;
}
