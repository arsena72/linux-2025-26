#include <cstddef>
#include <new>

template <typename T>
class allocator
{
public:

    using value_type = T;

    allocator() noexcept {}

    template <typename U>
    allocator(const allocator<U>& other) noexcept {}

    T* allocate(std::size_t n)
    {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n)
    {
        ::operator delete(p);
    }

    template <typename U>
    bool operator==(const allocator<U>& other) const noexcept { return true; }

    template <typename U>
    bool operator!=(const allocator<U>& other) const noexcept { return false; }
};
