/*
 * @Author: Tairan Gao
 * @Date:   2023-09-25 15:46:27
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-10-23 10:25:20
 */

#include <memory>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <cassert>

class String
{
public:
    String() : size_(0), data_(nullptr) {}
    String(char *data)
    {
        size_ = std::strlen(data);
        data_ = new char[size_ + 1];
        std::strncpy(data_, data, size_);
        data_[size_] = '\0';
    }
    ~String()
    {
        delete[] data_;
    }

    String(const String &other)
    {
        size_ = other.size_;
        data_ = new char[size_ + 1];

        std::strncpy(data_, other.data_, size_);
        data_[size_] = '\0';
    }

    String &operator=(const String &other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] data_;
        size_ = other.size_;
        data_ = new char[size_ + 1];

        std::strncpy(data_, other.data_, size_);
        data_[size_] = '\0';

        return *this;
    }

    String(String &&other)
    {
        size_ = other.size_;
        data_ = other.data_;

        other.size_ = 0;
        other.data_ = nullptr;
    }

    String &operator=(String &&other)
    {
        if (this == &other)
        {
            return *this;
        }
        delete[] data_;
        size_ = other.size_;
        data_ = other.data_;

        other.size_ = 0;
        other.data_ = nullptr;
        return *this;
    }

    String operator+(const String &other) const
    {
        char *new_data = new char[size_ + other.size_ + 1];
        std::strncpy(new_data, data_, size_);
        std::strncpy(new_data + size_, other.data_, other.size_);
        new_data[size_ + other.size_] = '\0';
        return String(new_data);
    }

    String &operator+=(const String &other)
    {
        size_t new_size = size_ + other.size_;
        char *new_data = new char[new_size];
        std::strncpy(new_data, data_, size_);
        std::strncpy(new_data + size_, other.data_, other.size_);
        new_data[size_ + other.size_] = '\0';
        delete[] data_;
        data_ = new_data;
        size_ = new_size;
        return *this;
    }
    size_t size() const { return size_; }

    const char *c_str() const
    {
        return data_;
    }

private:
    size_t size_;
    char *data_;
};

void test_constructors()
{
    String s1;
    assert(s1.size() == 0);

    String s2("Hello");
    assert(s2.size() == 5);
    assert(std::strcmp(s2.c_str(), "Hello") == 0);
}

void test_copy_constructor()
{
    String s1("Hello");
    String s2 = s1;
    assert(s2.size() == 5);
    assert(std::strcmp(s2.c_str(), "Hello") == 0);
}

void test_move_constructor()
{
    String s1("Hello");
    String s2 = std::move(s1);
    assert(s2.size() == 5);
    assert(std::strcmp(s2.c_str(), "Hello") == 0);
    assert(s1.size() == 0);
}

void test_copy_assignment()
{
    String s1("Hello");
    String s2;
    s2 = s1;
    assert(s2.size() == 5);
    assert(std::strcmp(s2.c_str(), "Hello") == 0);
}

void test_move_assignment()
{
    String s1("Hello");
    String s2;
    s2 = std::move(s1);
    assert(s2.size() == 5);
    assert(std::strcmp(s2.c_str(), "Hello") == 0);
    assert(s1.size() == 0);
}

void test_concatenation()
{
    String s1("Hello");
    String s2("World");
    String s3 = s1 + s2;
    assert(s3.size() == 10);
    assert(std::strcmp(s3.c_str(), "HelloWorld") == 0);

    s1 += s2;
    assert(s1.size() == 10);
    assert(std::strcmp(s1.c_str(), "HelloWorld") == 0);
}

int main()
{
    test_constructors();
    test_copy_constructor();
    test_move_constructor();
    test_copy_assignment();
    test_move_assignment();
    test_concatenation();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
