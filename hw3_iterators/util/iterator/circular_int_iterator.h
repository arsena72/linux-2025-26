#pragma once
#include <cstddef>
#include <iterator>

class circular_int_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = value_type*;
    using reference = value_type&;

    circular_int_iterator(pointer data, std::size_t size)
        : data(data), size(size), index(0) {}

    [[nodiscard]] reference operator*() const noexcept { return data[index]; }
    [[nodiscard]] pointer operator->() const noexcept { return &data[index]; }

    circular_int_iterator& operator++() noexcept {
        index = (index + 1) % size;
        return *this;
    }

    circular_int_iterator operator++(int) noexcept {
        circular_int_iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    friend bool operator==(const circular_int_iterator& a, const circular_int_iterator& b) noexcept {
        return a.data == b.data && a.index == b.index && a.size == b.size;
    }

    friend bool operator!=(const circular_int_iterator& a, const circular_int_iterator& b) noexcept {
        return !(a == b);
    }

private:
    pointer data;
    std::size_t size;
    std::size_t index;
};

class circular_int_iterator_builder {
public:
    circular_int_iterator_builder(int* data, std::size_t size)
        : data(data), size(size), iterator(data, size) {}

    int& get() noexcept { return *iterator; }

    circular_int_iterator& operator*() noexcept { return iterator; }

    circular_int_iterator_builder& operator++() noexcept {
        ++iterator;
        return *this;
    }

private:
    int* data;
    std::size_t size;
    circular_int_iterator iterator;
};