/*
 * @Author: Tairan Gao
 * @Date:   2023-10-17 21:41:18
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-10-19 02:07:42
 */

/*
 * Question:
 * In python there is list comprehension, how do we do it with C++?
 * I want to create a  function that takes a function F and a container X,
 * which contains a number of x, and I will then output new containerY,
 * where element of Y is y and y = F(x)
 */

#include <type_traits>
#include <iterator>
#include <algorithm> // for std::transform
#include <iostream>
#include <vector>
#include <deque>
#include <iostream>

template <
    template <typename, typename...> typename Container,
    typename Function,
    typename Element,
    typename... Args>
auto transform_container(const Container<Element, Args...> &input, Function func)
{
    // Deduce the type of the container elements after applying the function
    using FuncResultType = decltype(func(*std::begin(input)));

    // Remove const-ness and reference from the result type
    using CleanType = typename std::remove_const<typename std::remove_reference<FuncResultType>::type>::type;

    // Create a container of the appropriate type
    Container<CleanType, Args...> result;

    // Apply the function to each element in the input container
    std::transform(std::begin(input), std::end(input), std::back_inserter(result), func);

    return result;
}

int main()
{
    // Example with std::vector
    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto result_vec = transform_container(vec, [](int x)
                                          { return x * 2; });

    std::cout << "Result (vector): ";
    for (int x : result_vec)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // Example with std::deque
    std::deque<std::string> deq = {"1", "2", "3", "4", "5"};
    auto result_deq = transform_container(deq, [](const std::string &str)
                                          { return "Number: " + str; });

    std::cout << "Result (deque): ";
    for (const auto &str : result_deq)
    {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    return 0;
}
