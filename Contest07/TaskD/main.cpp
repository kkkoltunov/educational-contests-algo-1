#include <iostream>

struct TreeNode {
    int value;
    TreeNode *leftChildren;
    TreeNode *rightChildren;

    explicit TreeNode(int new_value) {
        value = new_value;
        leftChildren = nullptr;
        rightChildren = nullptr;
    }
};

class Tree {
private:
    TreeNode *root_;

    TreeNode *insertChildren(TreeNode *tree_node, int value) {
        if (tree_node == nullptr) {
            tree_node = new TreeNode(value);
        } else if (value < tree_node->value) {
            tree_node->leftChildren = insertChildren(tree_node->leftChildren, value);
        } else if (value > tree_node->value) {
            tree_node->rightChildren = insertChildren(tree_node->rightChildren, value);
        }

        return tree_node;
    }

    void deleteNode(TreeNode *tree_node) {
        if (tree_node) {
            deleteNode(tree_node->leftChildren);
            deleteNode(tree_node->rightChildren);
            delete tree_node;
        }
    }

    void printChildren(TreeNode *parent) {
        if (parent) {
            printChildren(parent->leftChildren);
            printChildren(parent->rightChildren);

            if (!parent->rightChildren && !parent->leftChildren) {
                std::cout << parent->value << "\n";
            }
        }
    }

public:
    Tree() {
        root_ = nullptr;
    }

    ~Tree() {
        deleteNode(root_);
    }

    void insert(int value) {
        root_ = insertChildren(root_, value);
    }

    void print() {
        printChildren(root_);
    }
};

int main() {
    Tree *tree = new Tree();

    int input;
    std::cin >> input;

    while (input != 0) {
        tree->insert(input);
        std::cin >> input;
    }

    tree->print();
    delete tree;

    return 0;
}
