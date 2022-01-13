#include <iostream>
#include <string>

struct TreeNode {
    int value;
    char color;
    int numberLeftChildren;
    int numberRightChildren;

    explicit TreeNode(int new_value, char new_color, int number_left_children,
                      int number_right_children) {
        value = new_value;
        color = new_color;
        numberLeftChildren = number_left_children;
        numberRightChildren = number_right_children;
    }
};

class Tree {
private:
    TreeNode *nodes_[20000001];
    bool is_tree_correct_;
    int size_;
    int root_;

    void deleteNode() {
        for (int i = 0; i < size_; ++i) {
            delete nodes_[i];
        }
    }

    void insertNodes() {
        int value;
        int number;
        std::cin >> number >> value;

        std::string left_children;
        std::string right_children;
        std::cin >> left_children >> right_children;

        char color;
        std::cin >> color;

        int node_left = -1;
        int node_right = -1;

        if (left_children != "null") {
            node_left = std::stoi(left_children) - 1;
        }

        if (right_children != "null") {
            node_right = std::stoi(right_children) - 1;
        }

        nodes_[number - 1] = new TreeNode(value, color, node_left, node_right);
    }

    int checkForRBTree(int number_node, char parent_color, int lower_value, int high_value) {
        if (number_node == -1) {
            return 1;
        }

        if (nodes_[number_node]->value < lower_value || nodes_[number_node]->value > high_value) {
            is_tree_correct_ = false;
        }

        if (nodes_[number_node]->color == 'R' && parent_color == 'R') {
            is_tree_correct_ = false;
        }

        int left_height =
            checkForRBTree(nodes_[number_node]->numberLeftChildren, nodes_[number_node]->color,
                           lower_value, nodes_[number_node]->value - 1);
        int right_height =
            checkForRBTree(nodes_[number_node]->numberRightChildren, nodes_[number_node]->color,
                           nodes_[number_node]->value + 1, high_value);

        if (left_height != right_height) {
            is_tree_correct_ = false;
        }

        if (nodes_[number_node]->color == 'B') {
            ++left_height;
        }

        return left_height;
    }

public:
    explicit Tree(int new_size, int new_root) {
        size_ = new_size;
        root_ = new_root - 1;
        is_tree_correct_ = true;
    }

    ~Tree() {
        deleteNode();
    }

    void inputData(int const &size_of_tree) {
        for (int i = 0; i < size_of_tree; ++i) {
            insertNodes();
        }
    }

    void checkForRBT() {
        checkForRBTree(root_, nodes_[root_]->color, -2000000001, 2000000001);
        if (!is_tree_correct_) {
            std::cout << "NO";
            return;
        }

        std::cout << "YES";
    }
};

int main() {
    int size_of_tree;
    int number_of_root;
    std::cin >> size_of_tree >> number_of_root;

    if (size_of_tree == 0) {
        std::cout << "YES";
        return 0;
    }
    Tree *tree = new Tree(size_of_tree, number_of_root);
    tree->inputData(size_of_tree);
    tree->checkForRBT();
    delete tree;

    return 0;
}
