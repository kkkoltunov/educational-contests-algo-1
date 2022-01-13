#include <iostream>

int64_t sum_all = 0;
int64_t size_all = 0;

struct Node {
public:
    int *keys;
    int minimumDegree;
    int numberOfKeys;
    bool leaf;
    Node **children;

    explicit Node(int minimum_degree, bool leaf) {
        this->minimumDegree = minimum_degree;
        this->leaf = leaf;
        keys = new int[2 * minimum_degree - 1];
        children = new Node *[2 * minimum_degree];
        numberOfKeys = 0;
    }

    ~Node() = default;

    void deleteNodes(Node *node) {
        if (node) {
            for (int i = 0; i < node->numberOfKeys; ++i) {
                if (!node->leaf) {
                    deleteNodes(node->children[i]);
                }
            }

            delete[] node->keys;
            delete[] node->children;
            delete node;
        }
    }

    void insertNonFull(int key) {
        int shift = numberOfKeys - 1;

        if (leaf) {
            while (shift >= 0 && keys[shift] > key) {
                keys[shift + 1] = keys[shift];
                --shift;
            }

            ++numberOfKeys;
            keys[shift + 1] = key;
        } else {
            while (shift >= 0 && keys[shift] > key) {
                --shift;
            }

            if (children[shift + 1]->numberOfKeys == 2 * minimumDegree - 1) {
                splitChild(shift + 1, children[shift + 1]);

                if (keys[shift + 1] < key) {
                    ++shift;
                }
            }
            children[shift + 1]->insertNonFull(key);
        }
    }

    void splitChild(int index, Node *split_node) {
        Node *new_node = new Node(split_node->minimumDegree, split_node->leaf);
        new_node->numberOfKeys = minimumDegree - 1;

        for (int i = 0; i < minimumDegree - 1; ++i) {
            new_node->keys[i] = split_node->keys[i + minimumDegree];
        }

        if (!split_node->leaf) {
            for (int i = 0; i < minimumDegree; ++i) {
                new_node->children[i] = split_node->children[i + minimumDegree];
            }
        }

        split_node->numberOfKeys = minimumDegree - 1;

        for (int i = numberOfKeys; i >= index + 1; --i) {
            children[i + 1] = children[i];
        }

        children[index + 1] = new_node;

        for (int i = numberOfKeys - 1; i >= index; --i) {
            keys[i + 1] = keys[i];
        }

        keys[index] = split_node->keys[minimumDegree - 1];
        ++numberOfKeys;
    }

    void findSumAndSize() {
        ++size_all;

        int index;
        for (index = 0; index < numberOfKeys; ++index) {
            if (!leaf) {
                children[index]->findSumAndSize();
            }

            sum_all += keys[index];
        }

        if (!leaf) {
            children[index]->findSumAndSize();
        }
    }

    Node *search(int key) {
        int index = 0;
        while (index < numberOfKeys && key > keys[index]) {
            index++;
        }

        if (keys[index] == key) {
            return this;
        }

        if (leaf) {
            return nullptr;
        }

        return children[index]->search(key);
    }
};

class BTree {
public:
    explicit BTree(int minimum_degree) {
        root_ = nullptr;
        this->minimum_degree_ = minimum_degree;
    }

    ~BTree() {
        root_->deleteNodes(root_);
    }

    void insert(int key) {
        if (root_) {
            if (root_->search(key)) {
                return;
            }

            if (root_->numberOfKeys == 2 * minimum_degree_ - 1) {
                Node *new_node = new Node(minimum_degree_, false);
                new_node->children[0] = root_;
                new_node->splitChild(0, root_);

                int counter = 0;
                if (new_node->keys[0] < key) {
                    ++counter;
                }
                new_node->children[counter]->insertNonFull(key);
                root_ = new_node;
            } else {
                root_->insertNonFull(key);
            }
        } else {
            root_ = new Node(minimum_degree_, true);
            root_->keys[0] = key;
            root_->numberOfKeys = 1;
        }
    }

    void findSumAndSize() const {
        if (root_) {
            size_all = 0;
            sum_all = 0;
            root_->findSumAndSize();
        }
    }

    [[nodiscard]] int64_t size() const {
        findSumAndSize();
        return size_all;
    }

    [[nodiscard]] int64_t sum() const {
        // findSumAndSize();
        return sum_all;
    }

private:
    Node *root_;
    int minimum_degree_;
};
