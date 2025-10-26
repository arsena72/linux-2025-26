#pragma once
#include <cstddef>
#include <iterator>

class reverse_array_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = value_type*;
    using reference = value_type&;

    explicit reverse_array_iterator(pointer ptr) noexcept : current(ptr) {}

    [[nodiscard]] reference operator*() const noexcept { return *current; }
    [[nodiscard]] pointer operator->() const noexcept { return current; }

    reverse_array_iterator& operator++() noexcept {
        --current;
        return *this;
    }

    reverse_array_iterator operator++(int) noexcept {
        reverse_array_iterator tmp = *this;
        --current;
        return tmp;
    }

    friend bool operator==(const reverse_array_iterator& a, const reverse_array_iterator& b) noexcept {
        return a.current == b.current;
    }

    friend bool operator!=(const reverse_array_iterator& a, const reverse_array_iterator& b) noexcept {
        return a.current != b.current;
    }

private:
    pointer current;
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