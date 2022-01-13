#include <iostream>

template <class KeyType, class ValueType>
struct Node {
    KeyType key_;
    ValueType value_;
    Node *next_;

    Node(KeyType, ValueType);
};

template <class KeyType, class ValueType>
Node<KeyType, ValueType>::Node(KeyType key_type, ValueType value_type) {
    key_ = key_type;
    value_ = value_type;
    next_ = nullptr;
}

// Хеш-таблица
template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
private:
    size_t size_;
    int count_elements_;
    double capacity_fill_;
    Func func_;
    Node<KeyType, ValueType> **nodes_;

public:
    HashTable();

    explicit HashTable(Func);

    HashTable(size_t, double, Func = std::hash<KeyType>());

    ~HashTable();

    void insert(KeyType, ValueType);

    ValueType *find(KeyType);

    void erase(KeyType);

    Node<KeyType, ValueType> &operator[](uint64_t);

    Node<KeyType, ValueType> at(uint64_t);

    size_t size() const;

    size_t capacity() const;

    void newTable();
};

int hash();

template <class KeyType, class ValueType, class Func>
HashTable<KeyType, ValueType, Func>::HashTable() {
    this->size_ = 100;
    nodes_ = new Node<KeyType, ValueType> *[100]{};
    this->capacity_fill_ = 0.5;
    this->count_elements_ = 0;
}

template <class KeyType, class ValueType, class Func>
HashTable<KeyType, ValueType, Func>::HashTable(Func func) {
    this->size_ = 100;
    nodes_ = new Node<KeyType, ValueType> *[100]{};
    this->capacity_fill_ = 0.5;
    this->func_ = func;
    this->count_elements_ = 0;
}

template <class KeyType, class ValueType, class Func>
HashTable<KeyType, ValueType, Func>::HashTable(size_t size, double capacity_fill, Func func) {
    this->size_ = size;
    nodes_ = new Node<KeyType, ValueType> *[size] {};
    if (capacity_fill <= 0 || capacity_fill > 1) {
        this->capacity_fill_ = 0.5;
    } else {
        this->capacity_fill_ = capacity_fill;
    }
    this->func_ = func;
    this->count_elements_ = 0;
}

template <class KeyType, class ValueType, class Func>
HashTable<KeyType, ValueType, Func>::~HashTable() {
    for (int i = 0; i < size_; ++i) {
        Node<KeyType, ValueType> *delete_node = nodes_[i];
        while (delete_node) {
            Node<KeyType, ValueType> *next_node = delete_node->next_;
            delete delete_node;
            delete_node = next_node;
        }
    }
    delete[] nodes_;
}

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::insert(KeyType key_type, ValueType value_type) {
    size_t hash_code = func_(key_type) % size_;

    Node<KeyType, ValueType> *node = nodes_[hash_code];

    if (!node) {
        nodes_[hash_code] = new Node<KeyType, ValueType>(key_type, value_type);
        ++count_elements_;
    } else {
        while (node->next_ && node->key_ != key_type) {
            node = node->next_;
        }
        if (node->key_ != key_type) {
            node->next_ = new Node<KeyType, ValueType>(key_type, value_type);
            ++count_elements_;
        } else {
            node->value_ = value_type;
        }
    }

    if (count_elements_ / (size_ * 1.0) >= capacity_fill_) {
        newTable();
    }
}

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::newTable() {
    count_elements_ = 0;
    size_ *= 2;
    Node<KeyType, ValueType> **old_nodes = nodes_;
    nodes_ = new Node<KeyType, ValueType> *[size_] {};

    for (int index = 0; index < size_ / 2; ++index) {
        Node<KeyType, ValueType> *new_node = old_nodes[index];
        while (new_node) {
            insert(new_node->key_, new_node->value_);
            new_node = new_node->next_;
        }

        Node<KeyType, ValueType> *old_node = old_nodes[index];
        while (old_node) {
            Node<KeyType, ValueType> *next_node = old_node->next_;
            delete old_node;
            old_node = next_node;
        }
    }
    delete[] old_nodes;
}

template <class KeyType, class ValueType, class Func>
ValueType *HashTable<KeyType, ValueType, Func>::find(KeyType key_type) {
    size_t hash_code = func_(key_type) % size_;
    Node<KeyType, ValueType> *node = nodes_[hash_code];
    if (node) {
        if (node->key_ == key_type) {
            return &node->value_;
        }
        node = node->next_;
        while (node) {
            if (node->key_ == key_type) {
                return &node->value_;
            }
            node = node->next_;
        }
    }
    return nullptr;
}

template <class KeyType, class ValueType, class Func>
void HashTable<KeyType, ValueType, Func>::erase(KeyType key_type) {
    size_t hash_code = func_(key_type) % size_;

    if (!nodes_[hash_code]) {
        return;
    }

    Node<KeyType, ValueType> *node_previous = nullptr;
    Node<KeyType, ValueType> *new_node = nodes_[hash_code];
    while (new_node) {
        if (new_node->key_ == key_type) {
            if (!node_previous) {
                nodes_[hash_code] = new_node->next_;
                new_node->next_ = nullptr;
                delete new_node;
                --count_elements_;
                return;
            }

            node_previous->next_ = new_node->next_;
            new_node->next_ = nullptr;
            delete new_node;
            --count_elements_;
            return;
        }

        node_previous = new_node;
        new_node = new_node->next_;
    }
}

template <class KeyType, class ValueType, class Func>
Node<KeyType, ValueType> &HashTable<KeyType, ValueType, Func>::operator[](uint64_t hash_code) {
    if (hash_code >= size_) {
        throw std::out_of_range("");
    }
    if (!nodes_[hash_code]) {
        throw std::runtime_error("");
    }

    Node<KeyType, ValueType> &value = *nodes_[hash_code];
    return value;
}

template <class KeyType, class ValueType, class Func>
Node<KeyType, ValueType> HashTable<KeyType, ValueType, Func>::at(uint64_t hash_code) {
    if (hash_code >= size_) {
        throw std::out_of_range("");
    }
    if (!nodes_[hash_code]) {
        throw std::runtime_error("");
    }

    return *nodes_[hash_code];
}

template <class KeyType, class ValueType, class Func>
size_t HashTable<KeyType, ValueType, Func>::size() const {
    return count_elements_;
}

template <class KeyType, class ValueType, class Func>
size_t HashTable<KeyType, ValueType, Func>::capacity() const {
    return size_;
}

int main() {
    HashTable<int, int> *hash_table = new HashTable<int, int>();
    delete hash_table;
}
