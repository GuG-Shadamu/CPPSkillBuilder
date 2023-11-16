/*
 * @Author: Tairan Gao
 * @Date:   2023-09-25 16:37:13
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-09-25 18:38:01
 */

#include <cstddef>
#include <memory>
#include <functional>

struct Control
{
    size_t shared_count_ = 0;
};

template <typename T, typename Deleter = std::default_delete<T>>
class SmartPtr
{
public:
    SmartPtr() : control(nullptr), data(nullptr), deleter(Deleter()) {}
    ~SmartPtr()
    {
        reset();
    }
    void reset()
    {
        if (control == nullptr)
        {
            return;
        }
        if (--control->shared_count_ == 0)
        {
            deleter(data);
            delete control;
            control = nullptr;
            data = nullptr;
        }
    }

    SmartPtr(T *raw_ptr, Deleter d = Deleter()) : control(new Control{}), data(raw_ptr), deleter(d)
    {
        control->shared_count_ = 1;
    }

    SmartPtr(const SmartPtr &other)
    {
        control = other.control;
        control->shared_count_ += 1;
        data = other.data;
    }

    SmartPtr &operator=(const SmartPtr &other)
    {
        if (this == &other)
        {
            return *this;
        }

        reset();

        control = other.control;
        control->shared_count_ += 1;
        data = other.data;
        return *this;
    }

    SmartPtr(SmartPtr &&other)
    {
        control = other.control;
        data = other.data;

        other.control = nullptr;
        other.data = nullptr;
    }

    SmartPtr &operator=(SmartPtr &&other)
    {
        if (this == &other)
        {
            return *this;
        }
        reset();
        control = other.control;
        data = other.data;
        other.control = nullptr;
        other.data = nullptr;
        return *this;
    }

    T *get() const
    {
        return data;
    }

    const T *c_get() const
    {
        return data;
    }

private:
    Control *control;
    T *data;
    Deleter deleter;
};

#include <iostream>
#include <cassert>

struct TestStruct
{
    static int instanceCount;
    TestStruct() { ++instanceCount; }
    ~TestStruct() { --instanceCount; }
};
int TestStruct::instanceCount = 0;

void test_default_constructor()
{
    SmartPtr<TestStruct> ptr;
    assert(ptr.get() == nullptr);
}

void test_parameterized_constructor()
{
    {
        SmartPtr<TestStruct> ptr(new TestStruct);
        assert(ptr.get() != nullptr);
        assert(TestStruct::instanceCount == 1);
    }
    assert(TestStruct::instanceCount == 0);
}

void test_copy_constructor()
{
    SmartPtr<TestStruct> ptr1(new TestStruct);
    {
        SmartPtr<TestStruct> ptr2 = ptr1;
        assert(ptr1.get() == ptr2.get());
        assert(TestStruct::instanceCount == 1);
    }
    assert(TestStruct::instanceCount == 1);
}

void test_move_constructor()
{
    SmartPtr<TestStruct> ptr1(new TestStruct);
    {
        SmartPtr<TestStruct> ptr2 = std::move(ptr1);
        assert(ptr1.get() == nullptr);
        assert(ptr2.get() != nullptr);
        assert(TestStruct::instanceCount == 1);
    }
    assert(TestStruct::instanceCount == 0);
}

void test_copy_assignment()
{
    SmartPtr<TestStruct> ptr1(new TestStruct);
    SmartPtr<TestStruct> ptr2;
    ptr2 = ptr1;
    assert(ptr1.get() == ptr2.get());
    assert(TestStruct::instanceCount == 1);
}

void test_move_assignment()
{
    SmartPtr<TestStruct> ptr1(new TestStruct);
    SmartPtr<TestStruct> ptr2;
    ptr2 = std::move(ptr1);
    assert(ptr1.get() == nullptr);
    assert(ptr2.get() != nullptr);
    assert(TestStruct::instanceCount == 1);
}

void test_reset()
{
    SmartPtr<TestStruct> ptr(new TestStruct);
    assert(TestStruct::instanceCount == 1);
    ptr.reset();
    assert(ptr.get() == nullptr);
    assert(TestStruct::instanceCount == 0);
}

void test_custom_deleter()
{
    bool deleterCalled = false;
    {
        SmartPtr<TestStruct, std::function<void(TestStruct *)>> ptr(
            new TestStruct,
            [&deleterCalled](TestStruct *p)
            {
                deleterCalled = true;
                delete p;
            });
    }
    assert(deleterCalled);
    assert(TestStruct::instanceCount == 0);
}

int main()
{
    test_default_constructor();
    test_parameterized_constructor();
    test_copy_constructor();
    test_move_constructor();
    test_copy_assignment();
    test_move_assignment();
    test_reset();
    test_custom_deleter();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
