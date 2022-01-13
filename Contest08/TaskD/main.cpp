#include <iostream>

template <class ValueType>
class RBTree {
public:
    RBTree() {
    }

    RBTree(const RBTree& other) {
        size_ = other.size_;
        if (other.root_ && !other.root_->is_nil) {
            root_ = new Node(other.root_, nullptr);
        }
    }

    RBTree& operator=(const RBTree& other) {
        this->size_ = other.size_;
        Node* was_root = this->root_;
        if (other.root_ && !other.root_->is_nil) {
            this->root_ = new Node(other.root_, nullptr);
        } else {
            this->root_ = nullptr;
        }
        delete was_root;
        return *this;
    }

    ~RBTree() {
        delete root_;
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void insert(const ValueType& key) {
        Node* node = new Node(key, 'R');
        if (root_ == nullptr || root_->is_nil) {
            if (root_ && root_->is_nil) {
                delete root_;
            }
            root_ = node;
        } else {
            Node* current_node = root_;
            while (!current_node->is_nil) {
                if (isEqual(current_node->key, node->key)) {
                    delete node;
                    return;
                } else {
                    if (current_node->key < node->key) {
                        current_node = current_node->right;
                    } else {
                        current_node = current_node->left;
                    }
                }
            }
            current_node = current_node->parent;
            node->parent = current_node;
            if (node->key < current_node->key) {
                delete current_node->left;
                current_node->left = node;
            } else {
                delete current_node->right;
                current_node->right = node;
            }
        }
        ++size_;
        fixInsertion(node);
    }

    void erase(const ValueType& key) {
        Node* current_node = root_;
        while (current_node && !isEqual(current_node->key, key) && !current_node->is_nil) {
            if (current_node->key < key) {
                current_node = current_node->right;
            } else {
                current_node = current_node->left;
            }
        }

        if (!current_node || current_node->is_nil) {
            return;
        }
        bool need_fix = true;
        if (current_node->left->is_nil && current_node->right->is_nil) {
            if (current_node->color == 'R') {
                need_fix = false;
            }
            current_node = eraseLeafNode(current_node);
        } else {
            if (current_node->left->is_nil ^ current_node->right->is_nil) {
                if (current_node->color == 'R') {
                    need_fix = false;
                }
                current_node = eraseNodeWithOneSon(current_node);
            } else {
                Node* next_node = current_node->right;
                while (!next_node->left->is_nil) {
                    next_node = next_node->left;
                }
                current_node->key = next_node->key;
                if (next_node->color == 'R') {
                    need_fix = false;
                }
                current_node = eraseNodeWithOneSon(next_node);
            }
        }
        --size_;
        if (need_fix) {
            fixErase(current_node);
        }
    }

    ValueType* lower_bound(const ValueType& key) const {  // NOLINT
        return lower_bound(root_, key);
    }

    ValueType* find(const ValueType& key) const {
        return find(root_, key);
    }

    ValueType* traversal() const {
        ValueType* arr = new ValueType[size_];
        int index = 0;
        traversal(root_, &index, arr);
        return arr;
    }

private:
    struct Node {
        ValueType key;

        char color;

        bool is_nil = false;

        Node *left = nullptr, *right = nullptr, *parent = nullptr;

        Node(bool is_nil, Node* parent) {
            this->is_nil = is_nil;
            this->parent = parent;
            color = 'B';
        }

        Node(const ValueType& key, const char color) {
            this->key = key;
            this->color = color;
            this->left = new Node(true, this);
            this->right = new Node(true, this);
        }

        Node(Node* node, Node* parent) {
            color = node->color;
            key = node->key;
            is_nil = node->is_nil;
            this->parent = parent;
            if (node->left) {
                left = new Node(node->left, this);
            }
            if (node->right) {
                right = new Node(node->right, this);
            }
        }

        ~Node() {
            if (left != nullptr) {
                delete left;
            }
            if (right != nullptr) {
                delete right;
            }
        }
    };

    Node* root_ = nullptr;

    size_t size_ = 0;

    bool isEqual(const ValueType& a, const ValueType& b) {
        return !(a < b || b < a);
    }

    bool isLeftSon(Node* node) {
        return node == node->parent->left;
    }

    void rightRotation(Node* node) {
        Node* left_node = node->left;
        left_node->parent = node->parent;
        if (node->parent != nullptr) {
            if (node->parent->key < node->key) {
                node->parent->right = left_node;
            } else {
                node->parent->left = left_node;
            }
        }
        node->parent = left_node;
        node->left = left_node->right;
        left_node->right->parent = node;
        left_node->right = node;
        if (left_node->parent == nullptr) {
            root_ = left_node;
        }
    }

    void leftRotation(Node* node) {
        Node* right_node = node->right;
        right_node->parent = node->parent;
        if (node->parent != nullptr) {
            if (node->parent->key < node->key) {
                node->parent->right = right_node;
            } else {
                node->parent->left = right_node;
            }
        }
        node->parent = right_node;
        node->right = right_node->left;
        right_node->left->parent = node;
        right_node->left = node;
        if (right_node->parent == nullptr) {
            root_ = right_node;
        }
    }

    void fixInsertion(Node* node) {
        if (node == root_) {
            node->color = 'B';
        } else {
            while (node != root_ && node->parent->color == 'R') {
                if (node->parent == root_) {
                    break;
                }
                Node* grand_node = node->parent->parent;
                if (grand_node->left->color == 'R' && grand_node->right->color == 'R') {
                    grand_node->color = 'R';
                    grand_node->left->color = 'B';
                    grand_node->right->color = 'B';
                    node = grand_node;
                } else {
                    if (isLeftSon(node->parent)) {
                        if (!isLeftSon(node)) {
                            leftRotation(node->parent);
                            node = node->left;
                        }
                        rightRotation(grand_node);
                        node->parent->color = 'B';
                        node->parent->right->color = 'R';
                        break;
                    } else {
                        if (isLeftSon(node)) {
                            rightRotation(node->parent);
                            node = node->right;
                        }
                        leftRotation(grand_node);
                        node->parent->color = 'B';
                        node->parent->left->color = 'R';
                        break;
                    }
                }
            }
            root_->color = 'B';
        }
    }

    Node* eraseLeafNode(Node* current_node) {
        Node* son = new Node(true, current_node->parent);
        if (current_node->parent) {
            if (isLeftSon(current_node)) {
                current_node->parent->left = son;
            } else {
                current_node->parent->right = son;
            }
        } else {
            root_ = son;
            son->parent = nullptr;
        }
        delete current_node;
        return son;
    }

    Node* eraseNodeWithOneSon(Node* current_node) {
        if (!current_node->left->is_nil) {
            current_node->left->parent = current_node->parent;
            if (current_node->parent) {
                if (isLeftSon(current_node)) {
                    current_node->parent->left = current_node->left;
                } else {
                    current_node->parent->right = current_node->left;
                }
            } else {
                root_ = current_node->left;
            }
            Node* son = current_node->left;
            son->parent = current_node->parent;
            current_node->left = nullptr;
            delete current_node;
            return son;
        } else {
            current_node->right->parent = current_node->parent;
            if (current_node->parent) {
                if (isLeftSon(current_node)) {
                    current_node->parent->left = current_node->right;
                } else {
                    current_node->parent->right = current_node->right;
                }
            } else {
                root_ = current_node->right;
            }
            Node* son = current_node->right;
            son->parent = current_node->parent;
            current_node->right = nullptr;
            delete current_node;
            return son;
        }
    }

    void fixErase(Node* node) {
        while (node != root_ && node->color == 'B') {
            if (isLeftSon(node)) {
                Node* brother = node->parent->right;
                if (brother->color == 'R') {
                    leftRotation(node->parent);
                    node->parent->color = 'R';
                    node->parent->parent->color = 'B';
                }
                brother = node->parent->right;
                if (brother->left->color == 'B' && brother->right->color == 'B') {
                    brother->color = 'R';
                    if (node->parent->color == 'R') {
                        node->parent->color = 'B';
                        node = root_;
                    } else {
                        node = node->parent;
                    }
                } else {
                    if (brother->left->color == 'R' && brother->right->color == 'B') {
                        brother->left->color = 'B';
                        brother->color = 'R';
                        rightRotation(brother);
                        brother = brother->parent;
                    }
                    brother->color = node->parent->color;
                    brother->right->color = 'B';
                    node->parent->color = 'B';
                    leftRotation(node->parent);
                    node = root_;
                }
            } else {
                Node* brother = node->parent->left;
                if (brother->color == 'R') {
                    rightRotation(node->parent);
                    node->parent->color = 'R';
                    node->parent->parent->color = 'B';
                }
                brother = node->parent->left;
                if (brother->left->color == 'B' && brother->right->color == 'B') {
                    brother->color = 'R';
                    if (node->parent->color == 'R') {
                        node->parent->color = 'B';
                        node = root_;
                    } else {
                        node = node->parent;
                    }
                } else {
                    if (brother->left->color == 'B' && brother->right->color == 'R') {
                        brother->right->color = 'B';
                        brother->color = 'R';
                        leftRotation(brother);
                        brother = brother->parent;
                    }
                    brother->color = node->parent->color;
                    brother->left->color = 'B';
                    node->parent->color = 'B';
                    rightRotation(node->parent);
                    node = root_;
                }
            }
        }
        node->color = 'B';
        root_->color = 'B';
    }

    ValueType* lower_bound(Node* current_node,            // NOLINT
                           const ValueType& key) const {  // NOLINT
        if (!current_node || current_node->is_nil) {
            return nullptr;
        }

        if (current_node->key < key) {
            return lower_bound(current_node->right, key);
        } else {
            if (key < current_node->key) {
                ValueType* result = lower_bound(current_node->left, key);
                if (result == nullptr) {
                    return &current_node->key;
                } else {
                    return result;
                }
            } else {
                return &current_node->key;
            }
        }
    }

    ValueType* find(Node* current_node, const ValueType& key) const {
        if (!current_node || current_node->is_nil) {
            return nullptr;
        }

        if (current_node->key < key) {
            return find(current_node->right, key);
        } else {
            if (key < current_node->key) {
                return find(current_node->left, key);
            } else {
                return &current_node->key;
            }
        }
    }

    void traversal(Node* current_node, int* index, ValueType* arr) const {
        if (!current_node || current_node->is_nil) {
            return;
        }
        traversal(current_node->left, index, arr);
        arr[(*index)++] = current_node->key;
        traversal(current_node->right, index, arr);
    }
};
