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

    int maxDepthChildren(TreeNode *parent) {
        if (parent) {
            int left_tree_max_depth = maxDepthChildren(parent->leftChildren);
            int right_tree_max_depth = maxDepthChildren(parent->rightChildren);

            if (left_tree_max_depth > right_tree_max_depth) {
                return left_tree_max_depth + 1;
            } else {
                return right_tree_max_depth + 1;
            }
        }

        return 0;
    }

    void deleteNode(TreeNode *tree_node) {
        if (tree_node) {
            deleteNode(tree_node->leftChildren);
            deleteNode(tree_node->rightChildren);
            delete tree_node;
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

    int maxDepth() {
        return maxDepthChildren(root_);
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

    std::cout << tree->maxDepth();
    delete tree;

    return 0;
}
