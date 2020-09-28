#ifndef GRAYSET_VECTOR_H
#define GRAYSET_VECTOR_H

#include "header.h"

template <typename T>
class Node {
public:
    T* _data;
    Node* _next;

public:
    Node() = delete;
    explicit Node(const T& value) {
        this->_data = new T(value);
        this->_next = nullptr;
    }
    bool isend() const { return (this->_next == nullptr); }
    const T& value() { return *this->_data; }
    ~Node() { free(this->_data); }
};

template <typename T>
class Vector {
private:
    size_t _size;
    Node<T>* _header;

public:
    Vector(): _size(0), _header(nullptr) {}
    size_t count() const { return this->_size; }

    void append(const T& value) {
        Node<T>* current = this->_header;
        auto next = new Node<T>(value);

        // For insertion as first element
        if (current == nullptr) {
            this->_header = next;
            this->_size += 1;
            return;
        }

        while (!current->isend())
            current = current->_next;
        current->_next = next;

        this->_size += 1;
    };

    const T& get(size_t index) {
        if (index >= this->_size || index < 0 || this->_header == nullptr)
            throw std::out_of_range("Invalid index value.");

        Node<T>* current = this->_header;
        for (size_t _ = 0; _ < index; _++)
            current = current->_next;
        return *current->_data;
    }

    bool empty() const {
        return (this->_size == 0);
    }

    bool exist(const T& value) const {
        Node<T>* current = this->_header;
        if (this->_header == nullptr)
            return false;

        while (!current->isend()) {
            if (current->value() == value)
                return true;
            current = current->_next;
        }

        // Check for last item
        if (current->value() == value)
            return true;

        return false;
    };

    // Remove one element
    void remove(const T& value) {
        Node<T>* current = this->_header;
        if (this->_header == nullptr)
            return;

        size_t index = 0;
        while (!current->isend()) {
            if (current->value() == value) {
                this->pop(index);
                return;
            }
            current = current->_next;
            index++;
        }
    }

    T& index(size_t index) {
        if (index >= this->_size || index < 0 || this->_header == nullptr)
            throw std::out_of_range("Invalid index value.");

        Node<T>* current = this->_header;
        for (size_t _ = 0; _ < index; _++) {
            current = current -> _next;
        }
        return *current->_data;
    }

    T pop(size_t index) {
        if (index >= this->_size || index < 0 || this->_header == nullptr)
            throw std::out_of_range("Invalid index value.");

        Node<T>* next = nullptr;
        Node<T>* previous = this->_header;
        Node<T>* current = this->_header;

        for (size_t _ = 0; _ < index; _++) {
            previous = current;
            current = current -> _next;
        }
        T value = *current->_data;
        this->_size -= 1;

        // For removing of first element
        if (current == this->_header){
            this->_header = current->_next;
            delete current;
            return value;
        }

        // For removing of last element
        if (current->isend()) {
            delete current;
            previous->_next = nullptr;
            return value;
        }

        next = current->_next;
        delete current;
        previous->_next = next;

        return value;
    };

    ~Vector() {
        Node<T>* next;
        Node<T>* current = this->_header;
        if (current == nullptr)
            return;

        while (!current->isend()) {
            next = current->_next;
            delete current;
            current = next;
        }
        delete current;
    };
};

#endif //GRAYSET_VECTOR_H
