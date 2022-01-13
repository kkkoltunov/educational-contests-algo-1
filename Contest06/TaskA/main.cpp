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
    int64_t size;

    List() {
        headElement = nullptr;
        lastElement = nullptr;
        size = 0;
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

        ++size;
    }

    void pushNode(Node *new_node) {
        if (isEmpty()) {
            headElement = new_node;
            lastElement = new_node;
            return;
        } else {
            lastElement->nextElement = new_node;
            lastElement = new_node;
        }
    }

    [[nodiscard]] bool isEmpty() const {
        return headElement == nullptr;
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

void mergeLists(const List &list_first, const List &list_second) {
    List merge_list;

    Node *head_from_first_list = list_first.headElement;
    Node *head_from_second_list = list_second.headElement;

    for (unsigned int i = 0; i < list_first.size + list_second.size; ++i) {
        if (head_from_first_list == nullptr && head_from_second_list == nullptr) {
            break;
        }

        if (head_from_first_list == nullptr) {
            while (head_from_second_list) {
                merge_list.pushNode(head_from_second_list);
                head_from_second_list = head_from_second_list->nextElement;
            }
            break;
        }

        if (head_from_second_list == nullptr) {
            while (head_from_first_list) {
                merge_list.pushNode(head_from_first_list);
                head_from_first_list = head_from_first_list->nextElement;
            }
            break;
        }

        if (head_from_first_list->value < head_from_second_list->value) {
            merge_list.pushNode(head_from_first_list);
            head_from_first_list = head_from_first_list->nextElement;
        } else if (head_from_first_list->value >= head_from_second_list->value) {
            merge_list.pushNode(head_from_second_list);
            head_from_second_list = head_from_second_list->nextElement;
        }
    }

    merge_list.print();
    merge_list.clearMemory();
}

int main() {
    List list_first;
    List list_second;

    int length_first;
    int length_second;

    std::cin >> length_first >> length_second;

    for (unsigned int i = 0; i < length_first; ++i) {
        int current_element;
        std::cin >> current_element;
        list_first.pushBack(current_element);
    }

    for (unsigned int i = 0; i < length_second; ++i) {
        int current_element;
        std::cin >> current_element;
        list_second.pushBack(current_element);
    }

    mergeLists(list_first, list_second);

    return 0;
}
