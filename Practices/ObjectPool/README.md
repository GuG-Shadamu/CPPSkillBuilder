# ObjectPool Practice

## Overview
This project contains the implementation of an `ObjectPool` template class in C++, all within a single file. The `ObjectPool` class efficiently manages a pool of objects, which is particularly useful in high-performance or real-time applications to minimize frequent allocation and deallocation of objects.

## Features
- **Templated Object Pool:** Generic implementation compatible with any object type.
- **Efficient Memory Management:** Manages a pool of objects, optimizing memory usage by reusing objects.
- **Customizable Pool Size:** The pool size is adjustable, allowing control over memory usage.



Example:
```cpp
ObjectPool<Foo> myPool(256);
Foo *myObject = myPool.alloc();
// Use the object...
myPool.free(myObject);
```

## Implementation

The ObjectPool class is implemented in the main.cpp file, along with a demonstration of its usage. The example showcases how to allocate and deallocate objects within the pool using a simple Foo class.