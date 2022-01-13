/*
 * This program implements a list that does different operations with O(max_node_size(N)) time.
 */

#include <iostream>
#include <string>
#include <cmath>

int max_node_size = 999;
int64_t mod = 3;
char operation = '+';

struct Node {
    int64_t* array;
    int size;
    int64_t sumMod, sumXor;
    Node* Next;

    Node() {
        array = new int64_t[2 * max_node_size + 1];
        size = 0;
        sumMod = sumXor = 0;
        Next = nullptr;
    }

    void add(int64_t value) {
        array[size++] = value;
        sumMod = (sumMod + value) % mod;
        sumXor = sumXor ^ value;
    }

    void change(int index, int64_t value) {
        array[index] = value;
        update();
    }

    void remove(int index) {
        for (int i = index; i < size - 1; ++i) {
            array[i] = array[i + 1];
        }
        --size;
        update();
    }

    void insert(int index, int64_t value) {
        for (int i = size; i > index; --i) {
            array[i] = array[i - 1];
        }
        array[index] = value;
        ++size;
        update();
    }

    void update() {
        sumMod = sumXor = 0;
        for (int i = 0; i < size; ++i) {
            sumMod = (sumMod + array[i]) % mod;
            sumXor = sumXor ^ array[i];
        }
    }

    ~Node() {
        delete[] array;
    }
};

class List {
    Node* head_;
    int size_;

public:
    List() {
        head_ = new Node();
        size_ = 0;
    }

    ~List() {
        Node* current = head_;
        while (current != nullptr) {
            Node* to_delete = current;
            current = current->Next;
            delete to_delete;
        }
    }

    void input(int n) {
        Node* current = head_;
        for (int i = 0; i < n; ++i) {
            int64_t x;
            std::cin >> x;
            if (current->size < max_node_size) {
                current->add(x);
            } else {
                Node* new_node = new Node();
                current->Next = new_node;
                new_node->add(x);
                current = current->Next;
            }
        }
        size_ = n;
    }

    int64_t at(int index) {
        Node* current = head_;
        int cnt = 0;
        while (cnt + current->size <= index) {
            cnt += current->size;
            current = current->Next;
        }
        return current->array[index - cnt];
    }

    void change(int index, int64_t value) {
        Node* current = head_;
        int cnt = 0;
        while (cnt + current->size <= index) {
            cnt += current->size;
            current = current->Next;
        }
        current->change(index - cnt, value);
    }

    void remove(int index) {
        --size_;
        Node* current = head_;
        Node* previous = nullptr;
        int cnt = 0;
        while (cnt + current->size <= index) {
            cnt += current->size;
            previous = current;
            current = current->Next;
        }
        current->remove(index - cnt);
        if (current->size < max_node_size && previous) {
            if (previous->size <= max_node_size) {
                for (int i = 0; i < current->size; ++i) {
                    previous->add(current->array[i]);
                }
                previous->Next = current->Next;
                delete current;
            } else {
                previous->size--;
                for (int i = current->size; i > 0; --i) {
                    current->array[i] = current->array[i - 1];
                }
                current->size++;
                current->array[0] = previous->array[previous->size];
                previous->update();
                current->update();
            }
        }
    }

    void insert(int index, int64_t value) {
        ++size_;
        Node* current = head_;
        int cnt = 0;
        while (current->Next && (cnt + current->size <= index)) {
            cnt += current->size;
            current = current->Next;
        }
        current->insert(index - cnt, value);
        if (current->size >= 2 * max_node_size) {
            Node* new_node = new Node();
            for (int i = max_node_size; i < current->size; ++i) {
                new_node->add(current->array[i]);
            }
            new_node->Next = current->Next;
            current->Next = new_node;
            current->size = max_node_size;
        }
        current->update();
    }

    int64_t prefixSum(int r) {
        Node* current = head_;
        int cnt = 0;
        int64_t sum = 0;
        while (current && (cnt + current->size <= r)) {
            cnt += current->size;
            if (operation == '+') {
                sum = (sum + current->sumMod) % mod;
            } else {
                sum = sum ^ current->sumXor;
            }
            current = current->Next;
        }
        if (current) {
            for (int i = cnt; i < r; ++i) {
                if (operation == '+') {
                    sum = (sum + current->array[i - cnt]) % mod;
                } else {
                    sum = sum ^ current->array[i - cnt];
                }
            }
        }
        return sum;
    }

    int64_t compute(int l, int r) {
        int64_t res;
        if (operation == '+') {
            res = (mod + prefixSum(r) - prefixSum(l)) % mod;
            res = (res + mod) % mod;
        } else {
            res = prefixSum(r) ^ prefixSum(l);
        }
        return res;
    }

    int getSize() {
        return size_;
    }
};

void answerQueries(int m, List* list) {
    std::string command;
    int position;
    int64_t value;
    for (int i = 0; i < m; ++i) {
        std::cin >> command;
        if (command == "at") {
            std::cin >> position;
            std::cout << list->at(position - 1) << '\n';
        } else if (command == "size") {
            std::cout << list->getSize() << '\n';
        } else if (command == "erase") {
            std::cin >> position;
            list->remove(position - 1);
        } else if (command == "change") {
            std::cin >> position >> value;
            list->change(position - 1, value);
        } else if (command == "insert") {
            std::cin >> position >> value;
            list->insert(position - 1, value);
        } else if (command == "compute") {
            int l, r;
            std::cin >> l >> r;
            std::cout << list->compute(l - 1, r) << '\n';
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> operation;
    if (operation == '+') {
        std::cin >> mod;
    }
    std::cin >> n;
    max_node_size = static_cast<int>(sqrt(n)) + 1;
    List* list = new List();
    list->input(n);
    std::cin >> q;
    answerQueries(q, list);
    delete list;
    return 0;
}


