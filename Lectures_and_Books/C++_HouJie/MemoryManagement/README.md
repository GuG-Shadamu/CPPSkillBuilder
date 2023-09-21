# C++ Memory Management


### C++ Memory Primitives:

| Allocate                 | Free                       | Category         | Can be Overload |
| ------------------------ | -------------------------- | ---------------- | --------------- |
| malloc()                 | free()                     | C function       | no              |
| new                      | delete                     | C++ expressions  | no              |
| ::operator new()         | ::operator delete()        | C++ function     | yes             |
| allocator<T>::allocate() | allocator<T>::deallocate() | STL C++ function | yes             |


### Overload Class Operator New & Delete

- Operator `new`'s first argument has to be `size_t` 

- the overload of `delete` will never be called except for the following case:
  - When Ctor throws, the corresponding overloaded version of `delete` will be called
  - if Operator `delete` does not cover all the `new` case, it won't throw (warning instead)

