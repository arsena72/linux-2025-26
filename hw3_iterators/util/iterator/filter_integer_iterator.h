#pragma once
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>

class filter_integer_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = value_type*;
    using reference = value_type&;

    filter_integer_iterator(pointer ptr, pointer end, std::function<bool(int)> pred)
        : current(ptr), end(end), predicate(std::move(pred)) {
        advance_to_valid();
    }

    [[nodiscard]] reference operator*() const noexcept { return *current; }
    [[nodiscard]] pointer operator->() const noexcept { return current; }

    filter_integer_iterator& operator++() noexcept {
        ++current;
        advance_to_valid();
        return *this;
    }

    filter_integer_iterator operator++(int) noexcept {
        filter_integer_iterator tmp = *this;
        ++(*this);
        return tmp;
    }

    friend bool operator==(const filter_integer_iterator& a, const filter_integer_iterator& b) noexcept {
        return a.current == b.current;
    }

    friend bool operator!=(const filter_integer_iterator& a, const filter_integer_iterator& b) noexcept {
        return a.current != b.current;
    }

private:
    pointer current;
    pointer end;
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
        : data(data), size(size), predicate(std::move(pred)) {}

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
