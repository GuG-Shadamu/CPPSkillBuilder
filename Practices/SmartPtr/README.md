# Custom Smart Pointer Implementation in C++

## Overview
This project includes a custom implementation of a smart pointer (`SmartPtr`) in C++. The implementation is designed to mimic the functionality of standard smart pointers in C++, such as `std::shared_ptr`. It demonstrates the core concepts of memory management, reference counting, and custom deleters.

## Features
- **Reference Counting:** Manages the lifetime of objects through reference counting.
- **Custom Deleter Support:** Allows the use of custom deleters.
- **Copy and Move Semantics:** Implements both copy and move constructors and assignment operators.
- **Automatic Resource Management:** Automatically deallocates resources when the last `SmartPtr` referencing an object is destroyed or reassigned.

## Implementation
- The `SmartPtr` class template manages the object using a pointer and a control block.
- `Control` struct to keep track of the shared count.
- Customizable deleter to provide flexibility in resource cleanup.
- Constructors for different scenarios (default, parameterized, copy, and move).
- Assignment operators for both copy and move semantics.
- `reset` method to manually reset the pointer.
- `get` method to access the underlying raw pointer.

## Testing
The implementation includes various test cases to validate the functionality:
- Constructors (default, parameterized, copy, and move).
- Copy and move assignment operators.
- Reset functionality and custom deleter handling.
- Proper reference counting and resource management.
