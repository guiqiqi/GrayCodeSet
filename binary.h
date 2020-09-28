#ifndef GRAYSET_BINARY_H
#define GRAYSET_BINARY_H

#include "header.h"

class Binary {

private:
    size_t _size;
    unsigned char* _pool;

public:
    Binary() = delete;

    // Copy constructor for vector using
    Binary(const Binary& bin): _size(bin._size) {
        size_t pool_size = this->_size / 8 + 1;
        this->_pool = new unsigned char[pool_size];
        memcpy(this->_pool, bin._pool, pool_size);
    }

    explicit Binary(size_t size): _size(size) {
        size_t pool_size = size / 8 + 1;
        this->_pool = new unsigned char[pool_size];
        memset(this->_pool, 0, pool_size);
    }

    void set(int index, bool truth) {
        if (index >= this->_size || index < 0)
            throw std::out_of_range("Invalid index");

        size_t byte_offset = (this->_size - index - 1) / 8;
        unsigned char* target = this->_pool + byte_offset;
        size_t offset = (this->_size - index) - byte_offset * 8;

        unsigned char bit = 0x01 << (8 - offset);
        if (truth)
            *target |= bit;
        else
            *target &= ~bit;
    }

    bool get(size_t index) const {
        if (index >= this->size() || index < 0)
            throw std::out_of_range("Invalid index");

        size_t byte_offset = (this->_size - index - 1) / 8;
        unsigned char* target = this->_pool + byte_offset;
        size_t offset = (this->_size - index) - byte_offset * 8;

        unsigned char bit = 0x01 << (8 - offset);
        return static_cast<bool>((*target & bit) >> (8 - offset));
    }

    long decimal() const {
        long value = 0;
        for (size_t _ = 0; _ < this->_size; _++) {
            if (this->get(_))
                value += 1u << _;
        }
        return value;
    }

    template <typename VT>
    void decimal(VT value) {
        auto ulconv = static_cast<unsigned long>(value);
        for (size_t power = 0; power < this->_size; power ++) {
            if (static_cast<bool>(ulconv & 1u << power))
                this->set(power, true);
            else
                this->set(power, false);
        }
    }

    size_t size() const { return this->_size; }
    ~Binary() { delete this->_pool; }
    friend std::ostream& operator<<(std::ostream&, const Binary&);
    friend bool operator==(const Binary&, const Binary&);
};

#endif //GRAYSET_BINARY_H
