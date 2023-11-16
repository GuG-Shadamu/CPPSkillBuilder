/*
 * @Author: Tairan Gao
 * @Date:   2023-09-22 10:45:26
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-09-26 12:09:29
 */

#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <memory>

template <typename T>
class CircularQueue
{
private:
    T *data_;
    size_t size_;
    size_t head_;
    size_t tail_;
    size_t capacity_;

    std::mutex mutex_;
    std::condition_variable cv_empty_;
    std::condition_variable cv_full_;

public:
    CircularQueue(size_t capacity) : size_(0), head_(0), tail_(0), capacity_(capacity)
    {
        std::allocator<T> alloc;
        data_ = alloc.allocate(capacity_);
    }

    ~CircularQueue()
    {
        std::allocator<T> alloc;
        for (size_t i = 0; i < size_; i++)
        {
            size_t idx = (head_ + i) % capacity_;
            data_[idx].~T();
        }
        alloc.deallocate(data_, capacity_);
    }

    void enqueue(const T &element)
    {
        std::unique_lock lock(mutex_);
        cv_full_.wait(lock, [this]
                      { return size_ < capacity_; });
        new (&data_[tail_]) T(std::move(element));
        tail_ = (tail_ + 1) % capacity_;
        ++size_;
        cv_empty_.notify_one();
    }

    T dequeue()
    {
        std::unique_lock lock(mutex_);
        cv_empty_.wait(lock, [this]
                       { return size_ > 0; });

        T element = std::move(data_[head_]);

        head_ = (head_ + 1) % capacity_;
        --size_;
        cv_full_.notify_one();
        return element;
    }

    // copy
    CircularQueue(const CircularQueue &other) = delete;
    CircularQueue &operator=(const CircularQueue &other) = delete;

    // move
    CircularQueue(CircularQueue &&other) noexcept
    {
        std::lock_guard<std::mutex> lock(other.mutex_);

        data_ = std::move(other.data_);

        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.head_ = 0;
        other.tail_ = 0;
        other.size_ = other.capacity_ = 0;
        other.data_ = nullptr;
    }

    CircularQueue &operator=(CircularQueue &&other)
    {
        if (this == &other)
        {
            return *this;
        }
        std::lock(mutex_, other.mutex_);
        std::lock_guard<std::mutex> lhs_lk(mutex_, std::adopt_lock);
        std::lock_guard<std::mutex> rhs_lk(other.mutex_, std::adopt_lock);

        data_ = std::move(other.data_);

        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.head_ = 0;
        other.tail_ = 0;
        other.size_ = other.capacity_ = 0;
        other.data_ = nullptr;
        return *this;
    }
};