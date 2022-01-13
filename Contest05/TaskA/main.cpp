#include <iostream>
#include <string>

class Stack {
 private:
    int64_t *stack_;
    int64_t size_;

 public:
    explicit Stack(int64_t size_stack) {
        stack_ = new int64_t[size_stack];
        size_ = 0;
    }

    ~Stack() = default;
    void push(const std::string &data) {
        stack_[size_] = std::stoi(data.substr(5, data.size()));
        ++size_;

        std::cout << "ok" << '\n';
    }

    void pop() {
        if (size_ == 0) {
            std::cout << "error" << '\n';
            return;
        }

        std::cout << stack_[size_ - 1] << '\n';

        stack_[size_ - 1] = 0;
        --size_;
    }

    void back() {
        if (size_ == 0) {
            std::cout << "error" << '\n';
            return;
        }

        std::cout << stack_[size_ - 1] << '\n';
    }

    [[nodiscard]] int64_t size() const {
        return size_;
    }

    void clear() {
        stack_ = new int64_t[10000000];
        size_ = 0;

        std::cout << "ok" << '\n';
    }
};

int main() {
    Stack stack(10000000);

    std::string input;
    std::getline(std::cin, input);

    while (input != "exit") {
        if (input == "pop") {
            stack.pop();
        } else if (input == "back") {
            stack.back();
        } else if (input == "size") {
            std::cout << stack.size() << '\n';
        } else if (input == "clear") {
            stack.clear();
        } else {
            stack.push(input);
        }

        std::getline(std::cin, input);
    }

    std::cout << "bye";
    return 0;
}
