/*
 * @Author: Tairan Gao
 * @Date:   2023-10-23 10:28:57
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-10-23 10:28:58
 */
#include <memory>  // for std::allocator
#include <utility> // for std::forward
#include <cassert> // for assert()

template <typename T, typename Allocator = std::allocator<T>>
class Vector
{
private:
    T *start_;
    T *end_;
    T *end_of_storage_;
    Allocator alloc_; // instance of the allocator

public:
    Vector() : start_(nullptr), end_(nullptr), end_of_storage_(nullptr), alloc_(Allocator()) {}
    ~Vector()
    {
        for (T *p = start_; p != end_; ++p)
        {
            alloc_.destroy(p); // Use the allocator to destroy elements
        }
        alloc_.deallocate(start_, capacity()); // Use the allocator to deallocate memory
    }

    // ... other member functions ...

    void reserve(size_t new_cap)
    {
        size_t prev_cap = capacity();
        size_t prev_size = size();
        if (new_cap <= prev_cap)
        {
            return;
        }
        T *new_memory = alloc_.allocate(new_cap); // Use the allocator to allocate memory

        // move existing elements to the new memory
        for (size_t i = 0; i < prev_size; ++i)
        {
            alloc_.construct(new_memory + i, std::move_if_noexcept(*(start_ + i)));
            alloc_.destroy(start_ + i); // destroy old object after moving
        }

        alloc_.deallocate(start_, prev_cap); // deallocate old memory

        start_ = new_memory;
        end_ = start_ + prev_size;
        end_of_storage_ = start_ + new_cap;
    }

    void push_back(const T &new_element)
    {
        if (end_ == end_of_storage_)
        {
            reserve(1 + 2 * capacity());
        }
        alloc_.construct(end_, new_element); // Use the allocator to construct a new element
        ++end_;
    }

    template <typename... Args>
    void emplace_back(Args &&...args)
    {
        if (end_ == end_of_storage_)
        {
            reserve(1 + 2 * capacity());
        }
        alloc_.construct(end_, std::forward<Args>(args)...); // Use the allocator to construct a new element
        ++end_;
    }

    void reset()
    {
        for (T *p = start_; p != end_; ++p)
        {
            alloc_.destroy(p); // Use the allocator to destroy elements
        }
        alloc_.deallocate(start_, capacity()); // Use the allocator to deallocate memory
        start_ = nullptr;
        end_ = nullptr;
        end_of_storage_ = nullptr;
    }
};
