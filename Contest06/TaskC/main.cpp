#include <iostream>
#include <string>

struct Node {
    Node *nextNode;
    Node *previousNode;
    int value;

    explicit Node(int value_input) {
        value = value_input;
        nextNode = nullptr;
        previousNode = nullptr;
    }
};

class List {
private:
    int size_;
    Node *head_element_;
    Node *tail_element_;

public:
    List() {
        head_element_ = nullptr;
        tail_element_ = nullptr;
        size_ = 0;
    }

    ~List() {

        while (head_element_) {
            tail_element_ = head_element_->nextNode;
            delete head_element_;
            head_element_ = tail_element_;
        }
    }

    bool isEmpty() {
        return head_element_ == nullptr;
    }

    void pushFront(int value) {
        Node *new_node = new Node(value);

        if (isEmpty()) {
            head_element_ = new_node;
            tail_element_ = new_node;
        } else {
            head_element_->previousNode = new_node;
            new_node->nextNode = head_element_;
            head_element_ = new_node;
        }

        ++size_;
    }

    void pushBack(int value) {
        Node *new_node = new Node(value);

        if (isEmpty()) {
            head_element_ = new_node;
            tail_element_ = new_node;
        } else {
            new_node->previousNode = tail_element_;
            tail_element_->nextNode = new_node;
            tail_element_ = new_node;
        }

        ++size_;
    }

    void reverse() {
        Node *current_node = head_element_;
        Node *previous_node = nullptr;
        Node *next_node;

        while (current_node) {
            next_node = current_node->nextNode;
            current_node->nextNode = previous_node;
            previous_node = current_node;
            current_node = next_node;
        }

        head_element_ = previous_node;
    }

    void insert(int value, int position) {
        Node *new_node = new Node(value);
        Node *current_node = head_element_;
        int find_position = 0;

        while (find_position != position) {
            current_node = current_node->nextNode;
            find_position++;
        }

        Node *next_node = current_node->nextNode;

        current_node->nextNode = new_node;
        new_node->previousNode = current_node;
        next_node->previousNode = new_node;
        new_node->nextNode = next_node;

        ++size_;
    }

    void remove(int position) {
        Node *current_node = head_element_;
        int find_position = 0;

        while (find_position != position + 1) {
            current_node = current_node->nextNode;
            find_position++;
        }

        if (current_node != tail_element_) {
            Node *previous_node = current_node->previousNode;
            Node *next_node = current_node->nextNode;

            previous_node->nextNode = next_node;
            next_node->previousNode = previous_node;
        } else {
            Node *previous_node = current_node->previousNode;
            previous_node->nextNode = nullptr;
            tail_element_ = previous_node;
        }

        delete current_node;
        --size_;
    }

    void print() {
        Node *element = head_element_;

        if (!element) {
            return;
        }

        while (element) {
            std::cout << element->value << " ";
            element = element->nextNode;
        }
    }
};

int main() {
    List list;

    int count_elements;
    int count_commands;

    std::cin >> count_elements >> count_commands;

    for (unsigned int i = 0; i < count_elements; ++i) {
        int current_element;
        std::cin >> current_element;
        list.pushBack(current_element);
    }

    std::string command;

    for (unsigned int i = 0; i < count_commands; ++i) {
        std::cin >> command;

        if (command == "push_front") {
            int input_value;
            std::cin >> input_value;
            list.pushFront(input_value);
        } else if (command == "push_back") {
            int input_value;
            std::cin >> input_value;
            list.pushBack(input_value);
        } else if (command == "insert") {
            int input_value;
            int input_position;
            std::cin >> input_value >> input_position;
            list.insert(input_value, input_position);
        } else if (command == "remove") {
            int input_position;
            std::cin >> input_position;
            list.remove(input_position);
        }
    }

    list.print();
    std::cout << '\n';
    list.reverse();
    list.print();

    return 0;
}
