# C++ Specific Design Pattern


## Resource Acquisition Is Initialization (RAII):

This is more of an idiom than a design pattern. In C++, resource management (like memory, file handles, network sockets) is often tied to the lifetime of an object. When an object is created (initialized), it acquires the resource, and when it's destroyed, it releases the resource. This ensures resource leaks are minimized and is fundamental to C++'s approach to resource management.


## Curiously Recurring Template Pattern (CRTP):

This is a C++ technique where a class Derived inherits from a base class template instantiated with Derived itself. It's a form of static polymorphism.
```cpp
template <typename Derived>
class Base {};

class Derived : public Base<Derived> {};
```

CRTP allows the base class to use methods of the derived class without them being virtual. 
Example:

```cpp
template <typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
    
    void anotherInterface() {
        // Some default behavior or additional behavior
    }
};

class Derived : public Base<Derived> {
public:
    void implementation() {
        // Derived class's specific behavior
    }
};

int main() {
    Derived d;
    d.interface();  // Calls Derived's implementation
}

```

### Pros:

1. Performance: Since there's no dynamic dispatch (like with virtual functions), the compiler can inline methods, leading to potentially more optimized code.
2. Static Polymorphism: Allows for polymorphic behavior determined at compile-time.

## Pimpl (Pointer to IMPLementation) Idiom

Famous Example: String class in C++

### Basic Structure

- Header:
```cpp
#include <memory> // for std::unique_ptr

class MyClassImpl; // forward declaration

class MyClass {
public:
    MyClass();
    ~MyClass();
    void someMethod();
    
private:
    std::unique_ptr<MyClassImpl> pImpl;
};

```



- Source File:
```cpp
#include "MyClass.h"

class MyClassImpl {
public:
    void someMethodImpl() {
        // Actual implementation here
    }
};

MyClass::MyClass() : pImpl(new MyClassImpl()) {}

MyClass::~MyClass() = default;

void MyClass::someMethod() {
    pImpl->someMethodImpl();
}
```



### Benefits

1. Reduced Compile-Time Dependencies: Changing the private members of MyClassImpl will not require recompilation of code that only depends on MyClass.h, thereby improving compilation times.

2. Encapsulation: The implementation details are completely hidden from the users of the class, which makes it easier to maintain and change the code without affecting client code.

3. Binary Compatibility: You can change the implementation details without affecting the layout or size of the MyClass object, which is crucial for maintaining binary compatibility in shared libraries.

4. Cleaner Interface: The public interface of the class is not cluttered with implementation details, making it easier to understand and use.

## Thread Safe Singleton

While the Singleton pattern exists in many languages, its implementation in C++ has unique challenges due to the language's multi-threading and initialization rules. Ensuring a thread-safe and correctly initialized Singleton in C++ requires specific techniques.

### C++11 and Later: Meyers' Singleton

With C++11, the language provides built-in thread safety for static local variables. This makes the Meyers' Singleton pattern both simple and thread-safe:

```cpp
class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;  // Guaranteed to be destroyed.
                                    // Instantiated on first use.
                                    // Thread safe in C++11 and later.
        return instance;
    }

    Singleton(Singleton const&) = delete;            // Don't allow copy construction
    void operator=(Singleton const&) = delete;       // Don't allow copy assignment

private:
    Singleton() {}  // Private constructor
};
```
