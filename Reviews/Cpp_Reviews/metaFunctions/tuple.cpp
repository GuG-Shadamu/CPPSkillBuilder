#include <iostream>

// Define a structure template to represent each element in the tuple
template <size_t Index, typename T>
struct TupleElement
{
    T value;
    TupleElement(const T &val) : value(val) {}
};

// Forward declaration of TupleImpl
template <size_t Index, typename... Types>
struct TupleImpl;

// Base case for the recursive tuple definition
template <size_t Index>
struct TupleImpl<Index>
{
};

// Recursive definition of a tuple
template <size_t Index, typename Head, typename... Tail>
struct TupleImpl<Index, Head, Tail...> : public TupleElement<Index, Head>, public TupleImpl<Index + 1, Tail...>
{
    TupleImpl(const Head &head, const Tail &...tail)
        : TupleElement<Index, Head>(head), TupleImpl<Index + 1, Tail...>(tail...) {}
};

// Define the Tuple type
template <typename... Types>
using Tuple = TupleImpl<0, Types...>;

// Function to get an element from a tuple by index
template <size_t Index, typename Head, typename... Tail>
constexpr decltype(auto) get(const TupleImpl<Index, Head, Tail...> &t)
{
    return static_cast<const TupleElement<Index, Head> &>(t).value;
}

int main()
{
    // Create a tuple of different types
    Tuple<int, double, char> t(1, 3.14, 'A');

    // Access elements of the tuple
    std::cout << "First element: " << get<0>(t) << std::endl;
    std::cout << "Second element: " << get<1>(t) << std::endl;
    std::cout << "Third element: " << get<2>(t) << std::endl;

    return 0;
}
