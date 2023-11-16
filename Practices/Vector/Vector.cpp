/*
 * @Author: Tairan Gao
 * @Date:   2023-10-22 21:44:03
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-10-23 10:26:18
 */

#include <cstddef>
#include <memory>
#include <cassert>

template <typename T>
class Vector
{

private:
    T *start_;
    T *end_;
    T *end_of_storage_;

public:
    Vector() : start_(nullptr), end_(nullptr), end_of_storage_(nullptr) {}
    ~Vector()
    {
        std::destroy(start_, end_);
        operator delete[](start_);
    }

    Vector(const Vector &other)
    {
        reserve(other.capacity());
        std::uninitialized_copy(other.start_, other.end_, start_);
        end_ = start_ + other.size();
        end_of_storage_ = start_ + other.capacity();
    }

    Vector(Vector &&other) noexcept
    {
        start_ = other.start_;
        end_ = other.end_;
        end_of_storage_ = other.end_of_storage_;
        other.start_ = nullptr;
        other.end_ = nullptr;
        other.end_of_storage_ = nullptr;
    }

    Vector &operator=(const Vector &other)
    {
        if (&other == this)
        {
            return *this;
        }
        reset();

        reserve(other.capacity());
        std::uninitialized_copy(other.start_, other.end_, start_);
        end_ = start_ + other.size();
        end_of_storage_ = start_ + other.capacity();
        return *this;
    }

    Vector &operator=(Vector &&other) noexcept
    {
        if (&other == this)
        {
            return *this;
        }
        reset();
        start_ = other.start_;
        end_ = other.end_;
        end_of_storage_ = other.end_of_storage_;
        other.start_ = nullptr;
        other.end_ = nullptr;
        other.end_of_storage_ = nullptr;
        return *this;
    }

    void resize(size_t new_size)
    {
        // new_size < prev_size
        for (T *p = start_ + new_size; p < end_; ++p)
        {
            p->~T();
        }

        if (new_size > capacity())
        {
            reserve(new_size * 2);
        }

        for (T *p = end_; p < new_size; ++p)
        {
            new (p) T();
        }
        end_ = start_ + new_size;
    }
    void reserve(size_t new_cap)
    {
        size_t prev_cap = capacity();
        size_t prev_size = size();
        if (new_cap <= prev_cap)
        {
            return;
        }
        T *new_memory = static_cast<T *>(operator new[](new_cap * sizeof(T)));

        try
        {
            std::uninitialized_move(start_, end_, new_memory);
        }
        catch (...)
        {
            operator delete[](new_memory);
            throw;
        }

        std::destroy(start_, end_);
        operator delete[](start_);

        start_ = new_memory;
        end_ = start_ + prev_size;
        end_of_storage_ = start_ + new_cap;
    }

    T &operator[](size_t index)
    {
        assert(index < size());
        return *(start_ + index);
    }

    T &front()
    {
        return *start_;
    }

    size_t size()
    {
        return end_ - start_;
    }

    size_t capacity()
    {
        return end_of_storage_ - start_;
    }

    bool empty()
    {
        return (size() == 0);
    }

    void pop_back()
    {
        if (end_ != start_)
        {
            (end_ - 1)->~T();
            --end_;
        }
    }
    void push_back(const T &new_element)
    {
        if (end_ == end_of_storage_)
        {
            reserve(1 + 2 * capacity());
        }
        new (end_) T(new_element);
        ++end_;
    }

    template <typename... Args>
    void emplace_back(Args &&...args)
    {
        if (end_ == end_of_storage_)
        {
            reserve(1 + 2 * capacity());
        }
        new (end_) T(std::forward<Args>(args)...);
        ++end_;
    }

    void reset()
    {
        std::destroy(start_, end_);
        operator delete[](start_);
        start_ = nullptr;
        end_ = nullptr;
        end_of_storage_ = nullptr;
    }
};
