#include <iostream>

struct Node {
public:
    int key;
    Node *parent;
    Node *leftChildren;
    Node *rightChildren;

    explicit Node(int value) {
        key = value;
        parent = nullptr;
        leftChildren = nullptr;
        rightChildren = nullptr;
    }
};

class SplayTree {
public:
    SplayTree() {
        root_ = nullptr;
    }

    ~SplayTree() {
        deleteNode(root_);
    }

    void insert(int key) {
        Node *node = new Node(key);
        Node *parent = nullptr;
        Node *root = root_;

        while (root) {
            parent = root;
            if (node->key < root->key) {
                root = root->leftChildren;
            } else if (node->key > root->key) {
                root = root->rightChildren;
            } else {
                delete node;
                return;
            }
        }

        node->parent = parent;
        if (parent == nullptr) {
            root_ = node;
        } else if (node->key < parent->key) {
            parent->leftChildren = node;
        } else {
            parent->rightChildren = node;
        }
    }

    [[nodiscard]] Node *find(int key) const {
        return findChildren(root_, key);
    }

    int splay(Node *node) {
        int counter = 0;

        if (node) {
            while (node->parent) {
                if (!node->parent->parent) {
                    if (node == node->parent->leftChildren) {
                        // Zig rotation.
                        rightRotate(node->parent);
                        ++counter;
                    } else {
                        // Zag rotation.
                        leftRotate(node->parent);
                        ++counter;
                    }
                } else if (node == node->parent->leftChildren &&
                           node->parent == node->parent->parent->leftChildren) {
                    // Zig-Zig rotation.
                    rightRotate(node->parent->parent);
                    rightRotate(node->parent);
                    counter += 2;
                } else if (node == node->parent->rightChildren &&
                           node->parent == node->parent->parent->rightChildren) {
                    // Zag-Zag rotation.
                    leftRotate(node->parent->parent);
                    leftRotate(node->parent);
                    counter += 2;
                } else if (node == node->parent->rightChildren &&
                           node->parent == node->parent->parent->leftChildren) {
                    // Zig-Zag rotation.
                    leftRotate(node->parent);
                    rightRotate(node->parent);
                    ++counter;
                } else {
                    // Zag-Zig rotation.
                    rightRotate(node->parent);
                    leftRotate(node->parent);
                    ++counter;
                }
            }
        }

        return counter;
    }

    [[nodiscard]] int getHeight() const {
        if (!root_) {
            return -1;
        }

        return maxDepthChildren(root_) - 1;
    }

private:
    Node *root_;

    void deleteNode(Node *tree_node) {
        if (tree_node) {
            deleteNode(tree_node->leftChildren);
            deleteNode(tree_node->rightChildren);
            delete tree_node;
        }
    }

    Node *findChildren(Node *parent, int key) const {
        if (!parent || parent->key == key) {
            return parent;
        } else if (key < parent->key) {
            return findChildren(parent->leftChildren, key);
        } else if (key > parent->key) {
            return findChildren(parent->rightChildren, key);
        }

        return nullptr;
    }

    int maxDepthChildren(Node *parent) const {
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

    void leftRotate(Node *node) {
        Node *right_children = node->rightChildren;
        node->rightChildren = right_children->leftChildren;
        if (right_children->leftChildren) {
            right_children->leftChildren->parent = node;
        }

        right_children->parent = node->parent;
        if (!node->parent) {
            this->root_ = right_children;
        } else if (node == node->parent->leftChildren) {
            node->parent->leftChildren = right_children;
        } else {
            node->parent->rightChildren = right_children;
        }

        right_children->leftChildren = node;
        node->parent = right_children;
    }

    void rightRotate(Node *node) {
        Node *left_children = node->leftChildren;
        node->leftChildren = left_children->rightChildren;
        if (left_children->rightChildren) {
            left_children->rightChildren->parent = node;
        }

        left_children->parent = node->parent;
        if (!node->parent) {
            this->root_ = left_children;
        } else if (node == node->parent->rightChildren) {
            node->parent->rightChildren = left_children;
        } else {
            node->parent->leftChildren = left_children;
        }

        left_children->rightChildren = node;
        node->parent = left_children;
    }
};
