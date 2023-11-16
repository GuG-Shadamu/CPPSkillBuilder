# Rule of Five

## 1. Destructor:

- Ordering:
  - **Construction**: **Base** Constrctor -> **Derived** Constructor
  - **Destructor**: **Derived** Destructor -> **Based** Destructor

- Virtual Destructor (Why do we need them):
  - Avoid Undefined Behavior
  - If a base class's destructor is not virtual, and you delete an object of a derived class through a pointer to the base class, then the derived class's destructor will not be called. This can lead to resource leaks if the derived class manages resources that need to be cleaned up in its destructor.
  - Making the destructor virtual ensures that the correct destructor is called based on the actual type of the object, not just the type of the pointer. This is consistent with the behavior of other virtual functions, which are resolved at runtime based on the actual type of the object.

        class Base {
        public:
            ~Base() { std::cout << "Base Destructor\n"; }
        };

        class Derived : public Base {
        public:
            ~Derived() { std::cout << "Derived Destructor\n"; }
        };

        int main() {
            Base* ptr = new Derived();
            delete ptr;  // Only "Base Destructor" will be printed, which is problematic!
        }


## 2. Copy Constructor:

    ClassName(const ClassName& other);


## 3. Copy Assignment Operator:


- Make sure to check for assignment to self:

        Class C
        {
            public:
            C& C::operator=(const C& rhs)
            {
                if (this == &rhs) return *this;
            }
        }


## 4. Move Constructor:

    ClassName(ClassName&& other);


## 5. Move Assignment Operator:

    ClassName& operator=(ClassName&& other);