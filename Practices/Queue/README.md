# Custom Queue Implementation in C++

## Overview
This project includes a custom implementation of a `Queue` class in C++. It's a templated class, allowing usage with various data types. The implementation demonstrates the core concepts of data structure design, memory management, and object-oriented programming in C++.

## Features
- **Templated Queue:** Supports different data types.
- **Dynamic Memory Management:** Handles dynamic allocation and deallocation of queue nodes.
- **Copy and Move Semantics:** Implements both copy and move constructors and assignment operators.
- **Exception Safety:** Provides basic exception handling for operations like `pop` and `front` on an empty queue.

## Implementation
- `Queue` class manages a linked list to store elements.
- `Node` struct as an inner class for the individual elements of the queue.
- `push` and `pop` methods for adding and removing elements.
- `front` method to access the front element.
- `size` and `empty` methods for size and state checking.
- Proper memory management in destructors and in assignment operators.
