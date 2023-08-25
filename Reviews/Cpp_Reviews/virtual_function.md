# Virtual Function

## Example:

    #include <iostream>

    // Base class
    class Shape {
    public:
        virtual void draw() const {
            std::cout << "Drawing a shape." << std::endl;
        }

        virtual ~Shape() {}  // Virtual destructor
    };

    // Derived class 1
    class Circle : public Shape {
    public:
        void draw() const override {
            std::cout << "Drawing a circle." << std::endl;
        }
    };

    // Derived class 2
    class Square : public Shape {
    public:
        void draw() const override {
            std::cout << "Drawing a square." << std::endl;
        }
    };

    int main() {
        Shape* shape1 = new Circle();
        Shape* shape2 = new Square();

        shape1->draw();  // Outputs: Drawing a circle.
        shape2->draw();  // Outputs: Drawing a square.

        delete shape1;
        delete shape2;

        return 0;
    }



## V-Ptr

- When there are virtual functions in a class C, There will a V-ptr (4 byte) pointer inside the data structure.
- Derived class has all member functions of Based class

## V-Table

V-Ptr points to V-Table

![demostration](imgs/vptr_vtable.png)

Each class has it's own virtual table.