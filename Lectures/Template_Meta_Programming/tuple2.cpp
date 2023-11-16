#include <iostream>
#include <type_traits>

// Define a structure template to represent each element in the tuple
template <size_t Index, typename T>
struct TupleElement
{
    T value;
    TupleElement(const T &val) : value(val) {}
};

// Forward declaration of the TupleImpl template
template <typename... Types>
struct TupleImpl;

// Base case specialization for the TupleImpl template
template <>
struct TupleImpl<>
{
};

// Recursive case specialization for the TupleImpl template
template <typename Head, typename... Tail>
struct TupleImpl<Head, Tail...>
{
    TupleElement<0, Head> headElement;
    TupleImpl<Tail...> tailTuple;

    TupleImpl(const Head &head, const Tail &...tail)
        : headElement(head), tailTuple(tail...) {}
};

template <typename... Types1, typename... Types2>
struct TupleCat<TupleImpl<Types1...>, TupleImpl<Types2...>>
{
    using type = TupleImpl<Types1..., Types2...>;
};

// Define the Tuple type
template <typename... Types>
using Tuple = TupleImpl<Types...>;

// Function to get an element from a tuple by index
template <size_t Index, typename Head, typename... Tail>
constexpr decltype(auto) get(const TupleImpl<Head, Tail...> &t)
{
    if constexpr (Index == 0)
        return t.headElement.value;
    else
        return get<Index - 1>(t.tailTuple);
}

int main()
{
    // Create a tuple of different types
    Tuple<int, double, char> t(1, 3.14, 'A');

    // Access elements of the tuple
    std::cout << "First element: " << get<0>(t) << std::endl;
    std::cout << "Second element: " << get<1>(t) << std::endl;
    std::cout << "Third element: " << get<2>(t) << std::endl;

    // Concatenate two tuples
    using Tuple1 = Tuple<int, double>;
    using Tuple2 = Tuple<char, bool>;
    using ConcatenatedTuple = typename TupleCat<Tuple1, Tuple2>::type;

    ConcatenatedTuple ct(1, 3.14, 'A', true);
    std::cout << "Fourth element of concatenated tuple: " << get<3>(ct) << std::endl;

    return 0;
}
