#include <iostream>
#include <string>

class Dequeue {
private:
    int64_t* dequeue_;
    int cursor_;

public:
    explicit Dequeue(int64_t dequeue_size) {
        dequeue_ = new int64_t[dequeue_size];

        cursor_ = -1;
    }

    void popFront() {
        std::cout << dequeue_[cursor_] << std::endl;

        dequeue_[cursor_] = 0;

        --cursor_;
    }

    void pushCentre(int n) {
        int centre = ((cursor_ + 1) / 2);

        for (int i = ++cursor_; i > centre; --i) {
            dequeue_[i] = dequeue_[i - 1];
        }

        dequeue_[centre] = n;
    }

    void pushBack(int n) {
        for (int i = ++cursor_; i > 0; --i) {
            dequeue_[i] = dequeue_[i - 1];
        }

        dequeue_[0] = n;
    }
};


int main() {
    Dequeue dequeue(100001);

    int n;
    std::cin >> n;
    std::cin.ignore();

    for (int i = 0; i < n; ++i) {
        std::string s;
        std::getline(std::cin, s);

        if (s.find("-") < s.length()) {
            dequeue.popFront();
        }

        if (s.find("+") < s.length()) {
            int index_of_space = s.find(" ");
            s.erase(0, index_of_space + 1);

            int citizen = atoi(s.c_str());

            dequeue.pushBack(citizen);
        }

        if (s.find("*") < s.length()) {
            int index_of_space = s.find(" ");
            s.erase(0, index_of_space + 1);

            int citizen = atoi(s.c_str());

            dequeue.pushCentre(citizen);
        }
    }
    return 0;
}
