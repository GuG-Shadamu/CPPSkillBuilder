/*
 * @Author: Tairan Gao
 * @Date:   2023-10-02 13:53:27
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-12-14 11:26:53
 */

#include <type_traits>
#include <iostream>
#include <typeinfo>

#include <tuple>

struct T
{
};

void test_typps()
{
    auto k = T();
    const T* v = &k;
    auto& s = v;

    if (std::is_same<decltype(s), T&&>::value)
    {
        std::cout << "Type of s is T&&" << std::endl;
    }
    else if (std::is_same<decltype(s), T&>::value)
    {
        std::cout << "Type of s is T&" << std::endl;
    }
    else if (std::is_same<decltype(s), T>::value)
    {
        std::cout << "Type of s is T" << std::endl;
    }
    else if (std::is_same<decltype(s), const T>::value)
    {
        std::cout << "Type of s is const T" << std::endl;
    }
    else if (std::is_same<decltype(s), T*>::value)
    {
        std::cout << "Type of s is T*" << std::endl;
    }
    else if (std::is_same<decltype(s), const T*>::value)
    {
        std::cout << "Type of s is const T*" << std::endl;
    }
    else if (std::is_same<decltype(s), const T&>::value)
    {
        std::cout << "Type of s is const T&" << std::endl;
    }
    else if (std::is_same<decltype(s), const T&&>::value)
    {
        std::cout << "Type of s is const T&&" << std::endl;
    }
    else if (std::is_same<decltype(s), const T*&>::value)
    {
        std::cout << "Type of s is const T*&" << std::endl;
    }
    else
    {
        std::cout << "Type of s is unknown" << std::endl;
    }
}

int main()
{

    auto a = 0;
    auto b = '\0';
    auto c = "0";
    auto t = std::make_tuple(a, b, c);
    auto& foo = *std::get<2>(t);
    if (std::is_same<decltype(foo), const char&>::value)
    {
        std::cout << "Type of s is const char&" << std::endl;
    }

    std::cout << "Type of foo: " << typeid(foo).name() << std::endl;

    return 0;
}