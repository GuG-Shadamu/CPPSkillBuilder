# Tiny Object Pool

*Learning from the book  Modern C++ Design, Generic Programming and Design Patterns Applied by Andrei Alexandrescu.*

---

## Overview

This project presents a custom memory allocator optimized for small object allocation in C++. It addresses the inefficiencies of the default C++ allocators `malloc`, `realloc`, and `free` which are typically optimized for larger objects. By focusing on small objects, this allocator aims to reduce memory overhead and fragmentation, leading to improved performance in applications where small allocations and deallocations are frequent.

## Resource
<https://loki-lib.sourceforge.net/html/>

## Motivation

The standard C++ memory allocators, while effective for large object management, are not optimized for small objects. This can result in performance bottlenecks, particularly in systems where memory efficiency is crucial. This project implements the concepts discussed in "Modern C++ Design: Generic Programming and Design Patterns Applied" by Andrei Alexandrescu, particularly focusing on efficient small object allocation.

## Modifications

The book, and thus its code, was written in 2001 while "Modern" C+ was not quite evolved as nowadays. Therefore my code modifies Andrei Alexandrescu's code a bit with some of the C++17 features, which only reflects my shallow understanding.

## Decisions / Explaination

### Chunk

- Using `Init` instead of a direct Constructor:
  - For efficiency reasons, Chunk does not define constructors, destructors, or assignment operator. Defining proper copy semantics at this level hurts efficiency at upper levels, where we store Chunk objects in a vector.

  - **Two-Phase Initialization**: The Init method suggests a two-phase initialization pattern. This means that the object is first constructed (possibly in an uninitialized or default state) and then explicitly initialized using Init.This pattern can be useful when the initialization process might fail or when the initialization data is not available at the time of object construction.

  - **Object Pooling or Reuse**: If Chunk objects are reused (for example, in an object pool), an Init method allows reinitialization of an existing object without destruction and reconstruction.This can be more efficient in certain scenarios, such as when dealing with a large number of objects that are frequently created and destroyed.


### FixedAllocator

- Using `Vector` instead of Linked-List like Scott suggested, will decrease the overhead for small object.  

### SmallObjAllocator

- TODO
