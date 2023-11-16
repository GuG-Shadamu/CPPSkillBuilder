/*
 * @Author: Tairan Gao
 * @Date:   2023-10-21 16:33:22
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-10-22 15:41:59
 */

#include <utility>
#include <memory>
#include <iostream>
#include <cassert>

template <typename T>
struct ObjectPool
{
private:
    union PoolItem
    {
        using StorageType = char[sizeof(T)];
        PoolItem *next;
        StorageType datum alignas(alignof(T));
    };

    size_t pool_size;
    std::unique_ptr<PoolItem[]> storage;
    PoolItem *free_list;

public:
    ObjectPool(size_t input_size) : pool_size(input_size), storage(new PoolItem[input_size])
    {
        for (size_t i = 0; i < input_size - 1; i++)
        {
            storage[i].next = &storage[i + 1];
        }
        storage[input_size - 1].next = nullptr;
        free_list = storage.get();
    }

    template <typename... Args>
    T *alloc(Args &&...args)
    {
        if (free_list == nullptr)
        {
            return nullptr;
        }

        PoolItem *current_item = free_list;
        free_list = current_item->next;

        T *result = reinterpret_cast<T *>(current_item->datum);
        new (result) T(std::forward<Args>(args)...);

        return result;
    }

    void free(T *t)
    {
        t->T::~T();

        PoolItem *current_item = reinterpret_cast<PoolItem *>(t);
        current_item->next = free_list;
        free_list = current_item;
    }
};

#define TRACE_METHOD() std::cout << this << " " << __PRETTY_FUNCTION__ << "\n";

struct Foo
{
    int x = 42;
    Foo() { TRACE_METHOD(); }
    Foo(int x) : x(x) { TRACE_METHOD(); }
    ~Foo() { TRACE_METHOD(); };
};

int main(int argc, char *argv[])
{
    ObjectPool<Foo> mp(256);

    Foo *p1 = mp.alloc();
    Foo *p2 = mp.alloc(44);

    std::cout << "p1->x=" << p1->x << "\n";
    std::cout << "p2->x=" << p2->x << "\n";

    mp.free(p1);
    mp.free(p2);

    return 0;
}
