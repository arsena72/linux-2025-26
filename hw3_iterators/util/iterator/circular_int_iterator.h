#pragma once
#include <cstddef>

class circular_int_iterator {
public:
    circular_int_iterator(int* data, std::size_t size)
        : data(data), size(size), index(0) {}

    int& operator*() const {
        return data[index];
    }

    circular_int_iterator& operator++() {
        index = (index + 1) % size;
        return *this;
    }

private:
    int* data;
    std::size_t size;
    std::size_t index;
};

class circular_int_iterator_builder {
public:
    circular_int_iterator_builder(int* data, std::size_t size)
        : data(data), size(size), iterator(data, size) {}

    int& get() { return *iterator; }

    circular_int_iterator& operator*() { return iterator; }
    circular_int_iterator_builder& operator++() {
        ++iterator;
        return *this;
    }

private:
    int* data;
    std::size_t size;
    circular_int_iterator iterator;
};
