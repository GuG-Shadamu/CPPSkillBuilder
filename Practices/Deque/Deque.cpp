/*
 * @Author: Tairan Gao
 * @Date:   2024-01-03 22:42:18
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2024-01-04 01:09:37
 */
#include <vector>
#include <list>
#include <iostream>
#include <cassert>
#include <exception>


template<typename T>
class SimpleDeque {

private:

    std::list<std::vector<T>> blocks;
    size_t block_size;
    size_t size_;
    size_t head_;
    size_t tail_;

    void allocate_front_block() {
        blocks.emplace_front();
        blocks.front().reserve(block_size);
    }

    void allocate_back_block() {
        blocks.emplace_back();
        blocks.back().reserve(block_size);
    }

    void initiate() {
        allocate_back_block();
        head_ = block_size / 2 - 1;
        tail_ = block_size / 2;
    }

public:

    SimpleDeque(size_t b_size) : block_size(b_size), size_(0) {
        initiate();
    }


    void push_back(const T& element) {
        if (tail_ == block_size) {
            allocate_back_block();
            tail_ = 0;
        }
        blocks.back()[tail_] = element;
        tail_++;
        size_++;
    }

    void push_front(const T& element) {
        blocks.front()[head_] = element;
        size_++;
        if (head_ == 0) {
            allocate_front_block();
            head_ = block_size - 1;
        }
        else {
            head_--;
        }
    }
    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Cannot pop from empty deuqe");
        }

        size_--;
        if (size_ == 0) {
            blocks.pop_back();
            initiate();
            return;
        }

        if (tail_ == 0) {
            blocks.pop_back();
            tail_ = block_size - 1;
            return;
        }
        tail_--;
    }

    void pop_front() {
        if (size_ == 0) {
            throw std::out_of_range("Cannot pop from empty deuqe");
        }

        size_--;
        if (size_ == 0) {
            blocks.pop_back();
            initiate();
            return;
        }
        if (head_ == block_size - 1) {
            blocks.pop_front();
            head_ = 0;
            return;
        }
        head_++;
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("Deque is empty");
        }

        if (head_ == block_size - 1) {
            return (*(++blocks.begin()))[0];
        }

        return  blocks.front()[head_ + 1];
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("Deque is empty");
        }
        if (tail_ == 0) {
            return (*(++blocks.end()))[block_size - 1];
        }
        return blocks.back()[tail_ - 1];
    }

    bool empty() {

        return (size_ == 0);
    }

};



void testBasicOperations() {
    SimpleDeque<int> deque(4); // Small block size for easier testing

    // Test basic push and pop
    deque.push_back(1);
    deque.push_back(2);
    assert(deque.back() == 2);
    assert(deque.front() == 1);

    deque.push_front(3);
    assert(deque.front() == 3);

    deque.pop_back();
    assert(deque.back() == 1);

    deque.pop_front();
    assert(deque.front() == 1);

    assert(!deque.empty());
    deque.pop_front();
    assert(deque.empty());

    std::cout << "testBasicOperations passed." << std::endl;
}

void testEdgeCases() {
    SimpleDeque<int> deque(2);

    // Fill the deque
    deque.push_back(1);
    deque.push_back(2);

    // Push more elements to test reallocation
    deque.push_back(3);
    assert(deque.back() == 3);

    // Test popping to empty and then pushing again
    deque.pop_back();
    deque.pop_back();
    deque.pop_back();
    assert(deque.empty());

    deque.push_front(4);
    assert(deque.front() == 4);

    std::cout << "testEdgeCases passed." << std::endl;
}

void testExceptionHandling() {
    SimpleDeque<int> deque(2);

    try {
        deque.pop_front();
        assert(false); // Should not reach here
    }
    catch (const std::out_of_range&) {
        // Expected exception
    }

    try {
        deque.pop_back();
        assert(false); // Should not reach here
    }
    catch (const std::out_of_range&) {
        // Expected exception
    }

    try {
        int a = deque.front();
        (void)a;
        assert(false); // Should not reach here
    }
    catch (const std::out_of_range&) {
        // Expected exception
    }

    try {
        int b = deque.back();
        (void)b;
        assert(false); // Should not reach here
    }
    catch (const std::out_of_range&) {
        // Expected exception
    }

    std::cout << "testExceptionHandling passed." << std::endl;
}

int main() {
    testBasicOperations();
    testEdgeCases();
    testExceptionHandling();
    // Add more tests as needed for 100% coverage

    std::cout << "All tests completed successfully." << std::endl;
    return 0;
}
