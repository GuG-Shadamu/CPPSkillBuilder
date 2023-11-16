# Custom String Class in C++

## Overview
This project includes a custom implementation of a `String` class in C++, designed to mimic some functionalities of the standard `std::string` class. It demonstrates the core concepts of memory management, object-oriented programming, and operator overloading in C++.

## Features
- **Dynamic Memory Management:** Allocates and manages memory for string data.
- **Deep Copy Semantics:** Implements copy constructor and copy assignment operator for deep copying strings.
- **Move Semantics:** Utilizes move constructor and move assignment for efficient memory transfers.
- **Operator Overloading:** Supports `+` and `+=` for string concatenation and `[]` for character access.
- **String Manipulation:** Provides basic string functionalities like concatenation and size retrieval.

## Implementation
The `String` class handles:
- Dynamic memory allocation and deallocation.
- Copy and move semantics for safe and efficient copying/moving of string data.
- String concatenation using overloaded operators.
- Access to string size and C-style string conversion.

## Test Cases
Includes test functions to validate:
- Constructors (default, parameterized, copy, and move).
- Copy and move assignment operators.
- String concatenation and size retrieval.
- Correctness of operations through `assert` statements.

## Usage
The implementation is demonstrated through various test cases in the `main` function. These test cases cover the creation, copying, moving, and concatenation of `String` objects.

```cpp
String s1("Hello");
String s2("World");
String s3 = s1 + s2;
```
