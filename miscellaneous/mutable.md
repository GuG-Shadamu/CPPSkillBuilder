# Mutable

1. Caching: If a class member is used to store a cache of data that is expensive to compute, you might declare it mutable. This allows the cache to be updated in a const member function, which doesn't logically change the object's state from the user's perspective.

2. Logging and Counting: If you want to keep track of how many times a const member function is called or log calls to these functions, a counter or logger can be declared mutable. This enables the logging or counting without violating the const-correctness.

3. Thread Synchronization: In multithreading environments, mutable can be used for mutexes or other synchronization primitives to allow for thread-safe modification or access within const member functions.

4. Lazy Initialization: Sometimes an object's member might not be initialized at the time of object construction and needs to be initialized later when it's first used. Declaring such members mutable allows their initialization within a const member function.

## Example 1

```cpp
class Entity
{
private:
    int m_DebugCount = 0;
    mutable std::string m_Name;
public:
    const std::string& GetName() const
    {
        m_DebugCount ++;
        return m_Name;
    }
}
```

## Example 2

```cpp
int main(){
    int x = 8;
    auto f = [=x]() mutable 
    { // by value (which will create a copy of x)
        x++;
        std::cout << "Hello" << std::endl;
    };
    // the mutable means that the function can change the values passed in by value
    // this will not change the value of x outside of the lamdba
    f();
    return 0;
}
```

