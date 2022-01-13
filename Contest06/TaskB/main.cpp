#include <iostream>

struct Node {
    int64_t value;
    Node *nextElement;

    explicit Node(int64_t value_input) {
        value = value_input;
        nextElement = nullptr;
    }
};

struct List {
    Node *headElement;
    Node *lastElement;

    List() {
        headElement = nullptr;
        lastElement = nullptr;
    }

    void pushBack(int64_t element) {
        Node *new_node = new Node(element);

        if (headElement == nullptr) {
            headElement = new_node;
            lastElement = new_node;
        } else {
            lastElement->nextElement = new_node;
            lastElement = new_node;
        }
    }

    void reverse() {
        Node *current_node = headElement;
        Node *previous_node = nullptr;
        Node *next_node;

        while (current_node) {
            next_node = current_node->nextElement;
            current_node->nextElement = previous_node;
            previous_node = current_node;
            current_node = next_node;
        }

        headElement = previous_node;
    }

    void clearMemory() {
        Node *current_node;

        while (headElement != nullptr) {
            current_node = headElement;
            headElement = headElement->nextElement;
            delete current_node;
        }

        headElement = nullptr;
    }

    void print() {
        Node *element = headElement;

        if (!element) {
            return;
        }

        while (element) {
            std::cout << element->value << " ";
            element = element->nextElement;
        }
    }
};

int main() {
    List list;

    int length_list;
    std::cin >> length_list;

    for (unsigned int i = 0; i < length_list; ++i) {
        int current_element;
        std::cin >> current_element;
        list.pushBack(current_element);
    }

    list.reverse();
    list.print();
    list.clearMemory();

    return 0;
}