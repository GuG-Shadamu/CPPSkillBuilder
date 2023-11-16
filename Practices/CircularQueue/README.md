# Custom Circular Queue Implementation in C++

## Overview
This project presents a custom implementation of a `CircularQueue` class in C++. The implementation focuses on providing a thread-safe queue using mutexes and condition variables, suitable for use in multi-threaded applications. The circular queue design is efficient for scenarios where a fixed-size, reusable queue is needed.

## Features
- **Thread Safety:** Ensures safe concurrent access using mutexes and condition variables.
- **Circular Queue Design:** Efficiently uses a fixed-size array to enable continuous reuse.
- **Concurrent Enqueue and Dequeue:** Allows multiple threads to add and remove elements safely.
- **Custom Memory Management:** Manages dynamic memory allocation and deallocation for queue elements.
- **Move Semantics:** Implements move constructor and assignment operator for efficient object transfers.

## Implementation
- The queue uses a templated array to store elements, allowing usage with various data types.
- Mutexes and condition variables handle synchronization, preventing race conditions and ensuring safe access in a concurrent environment.
- The enqueue operation inserts an element if the queue is not full, and the dequeue operation removes an element if the queue is not empty.
- Constructors and destructors manage the lifecycle of the queue, including proper handling of resources.

## Usage
The `CircularQueue` is particularly useful in producer-consumer scenarios where multiple threads need to access a common queue. It provides a reliable and efficient way to handle such interactions in a multi-threaded application.
