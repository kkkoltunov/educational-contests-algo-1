#include <iostream>
#include <set>

class MySet {
private:
    std::set<int> set_;
    bool flag_next_ = false;
    int last_value_ = 0;

public:
    void add(int number) {
        if (flag_next_) {
            set_.insert((number + last_value_) % 1000000000);
            flag_next_ = false;
            return;
        }
        set_.insert(number);
    }

    int next(int number) {
        if (set_.lower_bound(number) == set_.end()) {
            return -1;
        }
        flag_next_ = true;
        last_value_ = *set_.lower_bound(number);
        return last_value_;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_operations;
    std::cin >> number_operations;

    MySet my_set;
    for (int i = 0; i < number_operations; ++i) {
        char operation;
        int number;
        std::cin >> operation >> number;
        if (operation == '+') {
            my_set.add(number);
        } else {
            std::cout << my_set.next(number) << std::endl;
        }
    }

    return 0;
}
