#pragma once
#include <cstddef>

class reverse_array_iterator {
public:
    reverse_array_iterator(int* ptr) : current(ptr) {}

    int& operator*() const { return *current; }
    reverse_array_iterator& operator++() {
        --current;
        return *this;
    }

    bool operator!=(const reverse_array_iterator& other) const {
        return current != other.current;
    }

private:
    int* current;
};

class reverse_array_iterator_builder {
public:
    reverse_array_iterator_builder(int* data, std::size_t size)
        : data(data), size(size) {}

    reverse_array_iterator begin() const {
        return reverse_array_iterator(data + size - 1);
    }

    reverse_array_iterator end() const {
        return reverse_array_iterator(data - 1);
    }

private:
    int* data;
    std::size_t size;
};
