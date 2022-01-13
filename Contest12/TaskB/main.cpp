#include <iostream>
#include <set>
#include <iomanip>

double findCost(int number_elements) {
    std::multiset<int> multiset;

    for (size_t i = 0; i < number_elements; ++i) {
        int number;
        std::cin >> number;
        multiset.insert(number);
    }

    double money = 0;
    while (multiset.size() > 1) {
        std::_Rb_tree_const_iterator<int> first = multiset.begin();
        std::_Rb_tree_const_iterator<int> second = next(first);
        std::_Rb_tree_const_iterator<int> third = next(second);
        int sum = *first + *second;
        multiset.erase(first, third);
        money += sum;
        multiset.insert(sum);
    }
    return money;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_elements;
    std::cin >> number_elements;
    std::cout << std::setprecision(2);
    std::cout << std::fixed;
    std::cout << 0.05 * findCost(number_elements);
}
