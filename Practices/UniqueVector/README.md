# Unique Vector Template Metaprogram

## Overview
This project demonstrates advanced C++ template metaprogramming to create a unique sequence of compile-time integers by removing duplicates. The `vector` struct template accepts a sequence of integers and generates a new sequence, ensuring all elements are unique.

## Features
- **Compile-Time Deduplication:** Efficiently removes duplicate integers from a sequence during compile time.
- **Template Metaprogramming:** Leverages advanced C++ templates for type-level computations.
- **Type Traits & Conditional Compilation:** Utilizes `std::conditional_t` and type traits for compile-time logic and transformations.

## Usage
Define a `vector` with an integer sequence. The `unique` member type of this `vector` will be a new sequence with duplicates removed.

