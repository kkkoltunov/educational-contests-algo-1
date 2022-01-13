#include <iostream>
#include <string>

class Vector {
private:
    std::string *array_;
    int64_t size_;
    int64_t capacity_;

public:
    Vector() {
        size_ = 0;
        capacity_ = 1;
        array_ = new std::string[1];
    }

    void pushBack(std::string data) {
        if (size_ == capacity_) {
            std::string *temp = new std::string[2 * capacity_];

            for (int i = 0; i < capacity_; ++i) {
                temp[i] = array_[i];
            }

            delete[] array_;
            capacity_ *= 2;
            array_ = temp;
        }

        array_[size_] = data;
        ++size_;
    }

    bool contains(std::string data) {
        for (int i = 0; i < size_; ++i) {
            if (array_[i] == data) {
                return true;
            }
        }

        return false;
    }

    ~Vector() {
        delete[] array_;
    }
};

class BloomFilter {
private:
    int count_all_requests_ = 0;
    int count_wrong_requests_ = 0;
    size_t hashes_;
    size_t bits_;
    bool *array_;
    Vector vector_;

public:
    BloomFilter(size_t hashes, size_t bits);

    ~BloomFilter();

    void add(const std::string &obj);

    bool verify(const std::string &obj);

    double getFPRate() const;

    size_t numberOfHashFunctions() const;

    size_t numberOfBits() const;
};

BloomFilter::BloomFilter(size_t hashes, size_t bits) {
    this->hashes_ = hashes;
    this->bits_ = bits;
    array_ = new bool[bits]{};
}

BloomFilter::~BloomFilter() {
    delete[] array_;
}

void BloomFilter::add(const std::string &obj) {
    if (vector_.contains(obj)) {
        return;
    }

    vector_.pushBack(obj);
    array_[std::hash<std::string>{}(obj) % bits_] = true;
    for (size_t i = 1; i < hashes_; ++i) {
        array_[std::hash<std::string>{}(obj + std::to_string(i)) % bits_] = true;
    }
}

bool BloomFilter::verify(const std::string &obj) {
    ++count_all_requests_;

    if (!array_[std::hash<std::string>{}(obj) % bits_]) {
        return false;
    }
    for (size_t i = 1; i < hashes_; ++i) {
        if (!array_[std::hash<std::string>{}(obj + std::to_string(i)) % bits_]) {
            return false;
        }
    }

    if (!vector_.contains(obj)) {
        ++count_wrong_requests_;
    }

    return true;
}

double BloomFilter::getFPRate() const {
    if (count_all_requests_ == 0) {
        return 0;
    }

    return (1.0 * count_wrong_requests_) / (1.0 * count_all_requests_);
}

size_t BloomFilter::numberOfHashFunctions() const {
    return hashes_;
}

size_t BloomFilter::numberOfBits() const {
    return bits_;
}

int main() {
    BloomFilter bloom_filter(10, 10000);
    bloom_filter.add("1");
    bloom_filter.add("2");
    bloom_filter.add("1");
    bloom_filter.add("2");
    bloom_filter.add("12");
    bloom_filter.add("212");
    bloom_filter.add("32321");
    bloom_filter.add("223");
    bloom_filter.verify("3");
    bloom_filter.verify("3");
    bloom_filter.verify("3");
    bloom_filter.verify("3");
    bloom_filter.verify("3");
    bloom_filter.verify("3");
    std::cout << bloom_filter.getFPRate() << " " << bloom_filter.numberOfHashFunctions();
    return 0;
}
