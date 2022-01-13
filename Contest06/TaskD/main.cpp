#include <iostream>
#include <string>

struct Node {
    int value;
    Node *nextElement;

    explicit Node(int value_input) {
        value = value_input;
        nextElement = nullptr;
    }
};

class List {
private:
    Node *head_element_;
    Node *last_element_;

public:
    List() {
        head_element_ = nullptr;
        last_element_ = nullptr;
    }

    ~List() {
        Node *current_node = head_element_;

        while (head_element_ != nullptr) {
            head_element_ = current_node->nextElement;
            delete current_node;
            current_node = head_element_;
        }
    }

    void pushBack(int element) {
        Node *new_node = new Node(element);

        if (head_element_ == nullptr) {
            head_element_ = new_node;
            last_element_ = new_node;
        } else {
            last_element_->nextElement = new_node;
            last_element_ = new_node;
        }
    }

    void remove(int position) {
        Node *current_node = head_element_;
        Node *previous_node;
        int find_position = 0;

        while (find_position != position + 1) {
            previous_node = current_node;
            current_node = current_node->nextElement;
            ++find_position;
        }

        if (current_node != last_element_) {
            previous_node->nextElement = current_node->nextElement;
        } else {
            previous_node->nextElement = nullptr;
            last_element_ = previous_node;
        }

        delete current_node;
    }

    void insert(int value, int position) {
        Node *new_node = new Node(value);
        Node *current_node = head_element_;
        Node *next_node;
        int find_position = 0;

        while (find_position != position) {
            current_node = current_node->nextElement;
            ++find_position;
        }

        next_node = current_node->nextElement;
        current_node->nextElement = new_node;
        new_node->nextElement = next_node;
    }

    void print() {
        Node *element = head_element_;

        if (element == nullptr){
            return;
        }

        while (element != nullptr) {
            std::cout << element->value << " ";
            element = element->nextElement;
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

        if (command == "insert") {
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

    return 0;
}
