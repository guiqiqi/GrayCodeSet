#ifndef GRAYSET_SET_H
#define GRAYSET_SET_H

#include "header.h"
#include "vector.h"
#include "couple.h"

template <typename T>
unsigned int hash(size_t, const T&);

template <typename T>
class Set {
private:
    size_t _maxsize;
    Vector<T>** _slots;
    size_t _count;

public:
    Set() = delete;
    explicit Set(size_t maxsize): _maxsize(maxsize), _count(0) {
        if (maxsize <= 0)
            throw std::range_error("Set maxsize must greater than 0.");

        this->_slots = new Vector<T>*[maxsize];
        for (size_t _ = 0; _ < maxsize; _++)
            this->_slots[_] = new Vector<T>;
    }

    size_t count() const { return this->_count; }
    void add(const T& value) {
        const unsigned int key = hash(this->_maxsize, value);
        Vector<T>* slot = this->_slots[key];

        if (slot->exist(value))
            return;
        slot->append(value);
        this->_count++;
    }

    void remove(const T& value) {
        const unsigned int key = hash(this->_maxsize, value);
        Vector<T>* slot = this->_slots[key];
        slot->remove(value);
        this->_count--;
    }

    bool in(const T& value) const {
        const unsigned int key = hash(this->_maxsize, value);
        Vector<T>* slot = this->_slots[key];
        if (slot->empty()) return false;

        // Check if in slot
        if (slot->exist(value))
            return true;
        return false;
    }

    ~Set() {
        for (size_t _ = 0; _ < this->_maxsize; _++)
            delete this->_slots[_];
        delete[] this->_slots;
    }

public:
    class Iterator {
    private:
        Vector<T>** _slots;
        size_t _current;
        size_t _index;
        size_t _maxsize;

    public:
        Iterator() = delete;
        explicit Iterator(Vector<T>** slots, size_t current, size_t maxsize):
            _slots(slots), _index(0), _maxsize(maxsize), _current(current) {}

        const T& operator*() const {
            return this->_slots[this->_current]->get(this->_index);
        }

        // Find next value
        Iterator operator++() {
            if (this->_index < this->_slots[this->_current]->count() - 1) {
                this->_index++;
            } else {
                this->_index = 0;

                // Find for next valuable slot
                while (this->_current < this->_maxsize) {
                    this->_current++;
                    if (this->_current == this->_maxsize)
                        break;
                    if (!this->_slots[this->_current]->empty())
                        break;
                }
            }

            return *this;
        }

        bool operator!=(const Set<T>::Iterator& iter) const {
            return (this->_current != iter._current || this->_index != iter._index);
        }
    };

public:
    // Range based for loop supporting
    inline Iterator begin() const {

        // When empty slot
        if (this->_count == 0)
            return Iterator(this->_slots, 0, 0);

        for (size_t index = 0; index < this->_maxsize; index++)
            if (!this->_slots[index]->empty()) {
                return Iterator(this->_slots, index, this->_maxsize);
            }

        return Iterator(this->_slots, 0, 0);
    }

    // Search in reverse order for the last valuable slot
    inline Iterator end() const {

        // When empty slot
        if (this->_count == 0)
            return Iterator(this->_slots, 0, 0);

        for (size_t index = this->_maxsize - 1; index > 0; index--) {
            if (!this->_slots[index]->empty()) {
                return Iterator(this->_slots, this->_maxsize, this->_maxsize);
            }
        }

        return Iterator(this->_slots, 0, 0);
    }

#ifdef DEBUG
public:
    void _debug_vectors() const {
        std::cout << "Set count: " << this->count() << std::endl;
        std::cout << "Vectors begin:" << this->_slots << std::endl;
        for (auto index = 0; index < this->_maxsize; index++) {
            Vector<T>* ptr = this->_slots[index];
            std::cout << index + 1 << ". " << this->_slots + index
                      << '\t' << this->_slots[index] << '\t' << "Count: "
                      << ptr->count() << std::endl;
        }
        std::cout << "----------" << std::endl;
    }
#endif

public:

    // All arithmetic operations
    Set<T> intersection(const Set<T>& other) const {
        size_t size = std::max(this->_maxsize, other._maxsize);
        Set<T> result(size);
        for (auto&& value: other)
            if (this->in(value))
                result.add(value);

        return result;
    }

    Set<T> union_(const Set<T>& other) const {
        Set<T> result(this->_maxsize + other._maxsize);
        for (auto&& value: *this)
            result.add(value);
        for (auto&& value: other)
            result.add(value);

        return result;
    }

    Set<T> difference(const Set<T>& other) const {
        size_t size = std::max(this->_maxsize, other._maxsize);
        Set<T> result(size);
        for (const auto& value: *this)
            if (!other.in(value))
                result.add(value);

        return result;
    }

    Set<T> symdiff(const Set<T>& other) const {
        Set<T> parta = this->difference(other);
        Set<T> partb = other.difference(*this);
        return parta.union_(partb);
    }

    Set<T> complement(const Set<T>& universal) const {
        Set<T> result(universal._maxsize);
        for (const auto& value: universal)
            if (!this->in(value))
                result.add(value);

        return result;
    }

    Set<Couple<T, T>> sum(const Set<T>& other) const {
        size_t size = std::min(this->count(), other.count());
        Set<Couple<T, T>> result(size);

        for (const auto& valuea: *this) {
            for (const auto& valueb: other) {
                Couple<T, T> couple(valuea, valueb);
                result.add(couple);
                break;
            }
            if (size-- == 0) break;
        }
        return result;
    }

    Set<Couple<T, T>> product(const Set<T>& other) const {
        size_t size = this->count() * other.count();
        Set<Couple<T, T>> result(size);

        for (const auto& valuea: *this)
            for (const auto& valueb: other) {
                Couple<T, T> couple(valuea, valueb);
                result.add(couple);
            }

        return result;
    }

};

#endif //GRAYSET_SET_H
