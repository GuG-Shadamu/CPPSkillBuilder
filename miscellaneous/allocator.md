# Allocator


### Note from 
1. [Allocators: The Good Parts](https://www.youtube.com/watch?v=v3dz-AKOVL8)
2. [How to Write a Custom Allocator](https://www.youtube.com/watch?v=kSWfushlvB8)

---

1. ALlocator Role:
   1. allocation
   2. construction
   3. destruction
   4. deallocation

2. Idea of own allocator (for higher performance)
   1. stack-based allocation
   2. per-container private allocation
   3. per-thread allocation
   4. pooled / slab allocation
   5. Arena allocation
   6. Relocateable data

**Allocator Traits**

---

## std::pmr

`std::pmr` stands for "polymorphic memory resource" in C++. It is a part of the C++ Standard Library, introduced in C++17, under the `<memory_resource>` header. `std::pmr` provides facilities for efficient and customizable memory management, which is particularly useful in scenarios where memory allocation performance is critical, or where there is a need for non-standard memory allocation strategies.



