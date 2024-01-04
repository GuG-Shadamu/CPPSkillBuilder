# SimpleDeque

## Overview

`SimpleDeque` is a custom implementation of a double-ended queue (deque) in C++. It utilizes a combination of `std::list` and `std::vector` to efficiently manage elements. The deque allows for adding and removing elements from both ends with constant time complexity for most operations.

## Features

- **Dynamic Resizing**: Automatically resizes to accommodate new elements.
- **Efficient Access**: Provides efficient access to the front and back elements.
- **Exception Handling**: Throws exceptions for operations that are not valid, such as popping from an empty deque.

## Time Complexity of Operations

- `void push_back(const T& element)`:
  - Average Case: O(1)
  - Worst Case: O(N), amortized to O(1) over multiple operations
- `void push_front(const T& element)`:
  - Average Case: O(1)
  - Worst Case: O(N), amortized to O(1) over multiple operations
- `void pop_back()`:
  - Average Case: O(1)
  - Worst Case: O(N)
- `void pop_front()`:
  - Average Case: O(1)
  - Worst Case: O(N)
- `T& front()`: O(1)
- `T& back()`: O(1)
- `bool empty()`: O(1)
