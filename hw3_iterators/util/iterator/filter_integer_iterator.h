#pragma once
#include <cstddef>
#include <functional>

class filter_integer_iterator {
public:
    filter_integer_iterator(int* ptr, int* end, std::function<bool(int)> pred)
        : current(ptr), end(end), predicate(pred) {
        advance_to_valid();
    }

    int& operator*() const { return *current; }
    filter_integer_iterator& operator++() {
        ++current;
        advance_to_valid();
        return *this;
    }

    bool operator!=(const filter_integer_iterator& other) const {
        return current != other.current;
    }

private:
    int* current;
    int* end;
    std::function<bool(int)> predicate;

    void advance_to_valid() {
        while (current != end && !predicate(*current)) {
            ++current;
        }
    }
};

class filter_integer_iterator_builder {
public:
    filter_integer_iterator_builder(int* data, std::size_t size, std::function<bool(int)> pred)
        : data(data), size(size), predicate(pred) {}

    filter_integer_iterator begin() const {
        return filter_integer_iterator(data, data + size, predicate);
    }

    filter_integer_iterator end() const {
        return filter_integer_iterator(data + size, data + size, predicate);
    }

private:
    int* data;
    std::size_t size;
    std::function<bool(int)> predicate;
};