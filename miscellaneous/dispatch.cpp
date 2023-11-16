/*
 * @Author: Tairan Gao
 * @Date:   2023-08-25 11:14:10
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-08-25 11:29:34
 */
#include <iostream>

// Base class
class Animal
{
public:
    virtual void makeSound() const
    {
        std::cout << "Animal makes a sound." << std::endl;
    }
};

// Derived class
class Dog : public Animal
{
public:
    void makeSound() const override
    {
        std::cout << "Dog barks." << std::endl;
    }
};

// Another derived class
class Cat : public Animal
{
public:
    void makeSound() const override
    {
        std::cout << "Cat meows." << std::endl;
    }
};

int main()
{
    Animal *animalPtr; // Base class pointer

    Dog myDog;
    Cat myCat;

    // Dynamic dispatch in action
    animalPtr = &myDog;
    animalPtr->makeSound(); // Output: Dog barks.

    animalPtr = &myCat;
    animalPtr->makeSound(); // Output: Cat meows.

    Cat *myCat2 = new Cat;
    animalPtr = myCat2;
    animalPtr->makeSound(); // Output: Cat meows.

    delete myCat2;
    animalPtr->makeSound(); // Seg Fault

    return 0;
}
