#include <iostream>
#include <string>

class Dequeue {
 private:
    int64_t *dequeue_start_;
    int64_t *dequeue_end_;

    int index_start_;
    int index_end_;

    int size_;

 public:
    explicit Dequeue(int64_t dequeue_size) {
        dequeue_start_ = new int64_t[dequeue_size];
        dequeue_end_ = new int64_t[dequeue_size];

        index_start_ = 0;
        index_end_ = 0;

        size_ = 0;
    }

    void pushFront(const std::string &data) {
        dequeue_start_[index_start_] = std::stoi(data.substr(11, data.size()));
        ++index_start_;
        ++size_;

        std::cout << "ok" << '\n';
    }

    void pushBack(const std::string &data) {
        dequeue_end_[index_end_] = std::stoi(data.substr(10, data.size()));
        ++index_end_;
        ++size_;

        std::cout << "ok" << '\n';
    }

    void popFront() {
        if (size_ == 0) {
            std::cout << "error" << '\n';
            return;
        }

        if (index_start_ != 0) {
            std::cout << dequeue_start_[index_start_ - 1] << '\n';
            --index_start_;
            --size_;
        } else if (index_end_ != 0) {
            std::cout << dequeue_end_[0] << '\n';

            for (unsigned int i = 0; i < index_end_ - 1; ++i) {
                dequeue_end_[i] = dequeue_end_[i + 1];
            }

            --index_end_;
            --size_;
        }
    }

    void popBack() {
        if (size_ == 0) {
            std::cout << "error" << '\n';
            return;
        }

        if (index_end_ != 0) {
            std::cout << dequeue_end_[index_end_ - 1] << '\n';
            --index_end_;
            --size_;
        } else if (index_start_ != 0) {
            std::cout << dequeue_start_[0] << '\n';

            for (unsigned int i = 0; i < index_start_ - 1; ++i) {
                dequeue_start_[i] = dequeue_start_[i + 1];
            }

            --index_start_;
            --size_;
        }
    }

    void front() {
        if (size_ == 0) {
            std::cout << "error" << '\n';
            return;
        }

        if (index_start_ != 0) {
            std::cout << dequeue_start_[index_start_ - 1] << '\n';
        } else if (index_end_ != 0) {
            std::cout << dequeue_end_[0] << '\n';
        }
    }

    void back() {
        if (size_ == 0) {
            std::cout << "error" << '\n';
            return;
        }

        if (index_end_ != 0) {
            std::cout << dequeue_end_[index_end_ - 1] << '\n';
        } else if (index_start_ != 0) {
            std::cout << dequeue_start_[0] << '\n';
        }
    }

    [[nodiscard]] int64_t size() const {
        return size_;
    }

    void clear() {
        dequeue_start_ = new int64_t[100];
        dequeue_end_ = new int64_t[100];

        index_start_ = 0;
        index_end_ = 0;

        size_ = 0;

        std::cout << "ok" << '\n';
    }
};

int main() {
    Dequeue dequeue(100);

    std::string input;
    std::getline(std::cin, input);

    while (input != "exit") {
        if (input == "pop_front") {
            dequeue.popFront();
        } else if (input == "pop_back") {
            dequeue.popBack();
        } else if (input == "front") {
            dequeue.front();
        } else if (input == "back") {
            dequeue.back();
        } else if (input == "size") {
            std::cout << dequeue.size() << '\n';
        } else if (input == "clear") {
            dequeue.clear();
        } else if (input.substr(0, 10) == "push_front") {
            dequeue.pushFront(input);
        } else if (input.substr(0, 9) == "push_back") {
            dequeue.pushBack(input);
        }

        std::getline(std::cin, input);
    }

    std::cout << "bye";

    return 0;
}
