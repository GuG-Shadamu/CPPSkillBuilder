# Vector Implementation

## Overview
This project features a custom implementation of a `Vector` class in C++, designed to mimic the behavior of the standard library's `std::vector`. It demonstrates core features of dynamic array management, such as automatic resizing, copy semantics, and memory management.

## Features
- **Dynamic Array Management:** Automatically resizes to accommodate new elements.
- **Copy Semantics:** Implements copy constructor and copy assignment operator for deep copying.
- **Move Semantics:** Utilizes move constructor and move assignment operator for efficient transfers.
- **Memory Management:** Manages its own memory, ensuring proper allocation and deallocation.

## Usage
To use this `Vector` class, include the `main.cpp` file in your project. The class can be instantiated with any object type.

## Implementation
The Vector class is implemented in the main.cpp file. Key functionalities include:

- Element access (operator[ ])
- Capacity management (resize, reserve)
- Element addition/removal (push_back, pop_back, emplace_back)