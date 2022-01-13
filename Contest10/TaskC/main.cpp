#include <iostream>

class Vector {
private:
    int *array_;
    int size_;
    int capacity_;

public:
    Vector() {
        size_ = 0;
        capacity_ = 1;
        array_ = new int[1];
    }

    void pushBack(int data) {
        if (size_ == capacity_) {
            int *temp = new int[2 * capacity_];

            for (int i = 0; i < capacity_; ++i) {
                temp[i] = array_[i];
            }

            delete[] array_;
            capacity_ *= 2;
            array_ = temp;
        }

        array_[size_] = data;
        ++size_;
    }

    int operator[](int index) {
        return array_[index];
    }

    int size() {
        return size_;
    }

    ~Vector() {
        delete[] array_;
    }

    void print() {
        for (int i = 0; i < size_; ++i) {
            std::cout << array_[i] + 1 << " ";
        }
    }
};

int getRoot(int value, int *parent) {
    if (value == parent[value]) {
        return value;
    }
    return parent[value] = getRoot(parent[value], parent);
}

void unite(int first_value, int second_value, int *parent, Vector *vector) {
    first_value = getRoot(first_value, parent);
    second_value = getRoot(second_value, parent);
    if (vector[first_value].size() < vector[second_value].size()) {
        int temp = first_value;
        first_value = second_value;
        second_value = temp;
    }
    parent[second_value] = first_value;
    for (int i = 0; i < vector[second_value].size(); ++i) {
        vector[first_value].pushBack(vector[second_value][i]);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int parent[150001];
    int count_cat;
    std::cin >> count_cat;
    Vector *vector = new Vector[count_cat];

    for (int i = 0; i < count_cat; ++i) {
        parent[i] = i;
        vector[i].pushBack(i);
    }

    for (int i = 0; i < count_cat - 1; ++i) {
        int first_number;
        int second_number;
        std::cin >> first_number >> second_number;
        unite(first_number - 1, second_number - 1, parent, vector);
    }

    int root = getRoot(0, parent);
    for (int i = 0; i < vector[root].size(); ++i) {
        std::cout << vector[root][i] + 1 << " ";
    }
    delete[] vector;
    return 0;
}

