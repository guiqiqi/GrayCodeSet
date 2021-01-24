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
    size_t _size;
    Vector<T>** _slots;
    bool _unique;
    Vector<Couple<size_t, size_t>>* _registry;

public:
    Set() = delete;
    explicit Set(size_t slots, bool unique = true):
    _size(slots), _unique(unique), _registry(nullptr) {

        // Detect when number of slots is equal to 0
        if (slots <= 0)
            throw std::range_error("Number of slots must greater than 0.");

        this->_slots = new Vector<T>*[slots];
        for (size_t _ = 0; _ < slots; _++)
            this->_slots[_] = new Vector<T>;

        this->_registry = new Vector<Couple<size_t, size_t>>;
    }

    inline size_t count() const {
        return this->_registry->count();
    }

    void add(const T& value) {
        const unsigned int key = hash(this->_size, value);
        Vector<T>* slot = this->_slots[key];

        // Use the short-circuit theorem to check whether the same value exists
        if (this->_unique && slot->exist(value))
            return;

        // Add to registry
        this->_registry->append(Couple<size_t, size_t>(key, slot->count()));
        slot->append(value);
    }

    void remove(const T& value) {
        const unsigned int key = hash(this->_size, value);
        Vector<T>* slot = this->_slots[key];

        // Remove from registry
        slot->remove(value);
        this->_registry->remove(Couple<size_t, size_t>(key, slot->count()));
    }

    bool in(const T& value) const {
        const unsigned int key = hash(this->_size, value);
        Vector<T>* slot = this->_slots[key];
        if (slot->empty()) return false;

        // Check if in slot
        if (slot->exist(value))
            return true;
        return false;
    }

    bool multiple() const {
        return not this->_unique;
    }

    ~Set() {
        for (size_t _ = 0; _ < this->_size; _++)
            delete this->_slots[_];
        delete[] this->_slots;
        if (this->_registry != nullptr)
            delete this->_registry;
    }

public:
    class Iterator {
    private:
        size_t _index;
        Vector<T>** _slots;
        Vector<Couple<size_t, size_t>>* _registry;

    public:
        Iterator() = delete;
        explicit Iterator(Vector<T>** slots, Vector<Couple<size_t, size_t>>* registry, size_t index = 0):
            _registry(registry), _slots(slots), _index(index) {};
        const T& operator*() const {
            const Couple<size_t, size_t> position = this->_registry->index(this->_index);
            size_t slot = position.first();
            size_t index = position.second();
            return this->_slots[slot]->index(index);
        }
        Iterator operator++() {
            this->_index++;
            return *this;
        }
        bool operator!=(const Set<T>::Iterator& iter) {
            return this->_index != iter._index;
        }

    };

public:
    Iterator begin() const { return Iterator(this->_slots, this->_registry); }
    Iterator end() const { return Iterator(this->_slots, this->_registry,
                                           this->_registry->count()); }

#ifdef DEBUG
public:
    void _debug_vectors() const {
        std::cout << "Set count: " << this->count() << std::endl;
        std::cout << "Vectors begin:" << this->_slots << std::endl;
        for (auto index = 0; index < this->_size; index++) {
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
        size_t size = std::max(this->_size, other._size);
        Set<T> result(size, this->_unique);
        for (auto&& value: other)
            if (this->in(value))
                result.add(value);

        return result;
    }

    Set<T> union_(const Set<T>& other) const {
        Set<T> result(this->_size + other._size, this->_unique);
        for (auto&& value: *this)
            result.add(value);
        for (auto&& value: other)
            result.add(value);

        return result;
    }

    Set<T> difference(const Set<T>& other) const {
        size_t size = std::max(this->_size, other._size);
        Set<T> result(size, this->_unique);
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
        Set<T> result(universal._size, this->_unique);
        for (const auto& value: universal)
            if (!this->in(value))
                result.add(value);

        return result;
    }

    Set<Couple<T, T>> sum(const Set<T>& other) const {
        size_t size = std::min(this->_size, other._size);
        Set<Couple<T, T>> result(size, this->_unique);

        // No requirement for end iter cuz size has been defined
        Set<T>::Iterator this_iter = this->begin();
        Set<T>::Iterator other_iter = other.begin();
        Set<T>::Iterator this_stop = this->end();
        Set<T>::Iterator other_stop = other.end();

        // Fix Empty set bug
        while (this_iter != this_stop && other_iter != other_stop) {
            const T& value_a(*this_iter);
            const T& value_b(*other_iter);
            Couple<T, T> couple(value_a, value_b);
            result.add(couple);

            // Increment for iterators
            ++this_iter; ++other_iter;
        }

        return result;
    }

    Set<Couple<T, T>> product(const Set<T>& other) const {
        size_t size = this->_size * other._size;
        Set<Couple<T, T>> result(size, this->_unique);

        for (const auto& value_a: *this)
            for (const auto& value_b: other) {
                Couple<T, T> couple(value_a, value_b);
                result.add(couple);
            }

        return result;
    }

    unsigned int multiplicity(const T& element) const {
        unsigned int count = 0;
        for (const auto& value: *this) {
            if (element == value)
                count++;
        }
        return count;
    }

    Vector<Couple<T, unsigned int>> analysis() const {
        // Find all significant elements
        Set<T> unique(this->_size);
        for (const auto element: *this)
            unique.add((element));

        // For all unique elements find multiplicity
        Vector<Couple<T, unsigned int>> result;
        for (const auto element: unique)
            result.append(Couple<T, unsigned int>(element, this->multiplicity(element)));

        return result;
    }

};

#endif //GRAYSET_SET_H
