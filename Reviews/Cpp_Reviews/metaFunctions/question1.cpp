/*
 * @Author: Tairan Gao
 * @Date:   2023-10-16 17:37:27
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-10-17 19:10:06
 */

#include <iostream>
#include <type_traits>

namespace
{

    /**
     * 1. Define Vector, a template level list of integers.
     * Hint: Use non-type template parameter pack.
     */

    template <int...>
    struct Vector
    {
    };

    static_assert(std::is_same_v<Vector<1, 2>, Vector<1, 2>>);

    /**
     * 2. Define function print() that prints Vector-s.
     * Example: print(Vector<1,2,3>{}); // prints "1 2 3" (newline)
     * See main() below.
     */

    template <int... T>
    void print(Vector<T...>) // empty vector case
    {
        std::cout << std::endl;
    }

    template <int H>
    void print(Vector<H>)
    {
        std::cout << H << std::endl;
    }

    template <int H, int... T>
    void print(Vector<H, T...>)
    {
        std::cout << H << " ";
        print(Vector<T...>{});
    }

    /**
     * 3. Define Prepend.
     * Hint: Use `using type = ...` inside a struct that has both non-type and type template parameters.
     */

    template <int H, typename V>
    struct Prepend;

    template <int H, int... T>
    struct Prepend<H, Vector<T...>>
    {
        using type = Vector<H, T...>;
    };

    static_assert(std::is_same_v<Prepend<1, Vector<2, 3>>::type, Vector<1, 2, 3>>);

    /**
     * 4. Define PrependT that can be used without ::type.
     * Hint: See how enable_if_t is defined in terms of enable_if.
     *
     * This technique is not used further to reduce boilerplate.
     */

    template <int H, typename V>
    using PrependT = typename Prepend<H, V>::type;

    static_assert(std::is_same_v<PrependT<1, Vector<2, 3>>, Vector<1, 2, 3>>);

    /**
     * 5. Define Append.
     */

    template <int H, typename V>
    struct Append;

    template <int N, int H, int... T>
    struct Append<N, Vector<H, T...>>
    {
        using type = typename Prepend<H, typename Append<N, Vector<T...>>::type>::type;
    };

    template <int N>
    struct Append<N, Vector<>>
    {
        using type = Vector<N>;
    };

    static_assert(std::is_same_v<Append<4, Vector<1, 2, 3>>::type, Vector<1, 2, 3, 4>>);

    /**
     * 6. Define PopBack.
     */

    template <typename V>
    struct PopBack;

    template <int H, int... T>
    struct PopBack<Vector<H, T...>>
    {
        using type = typename Prepend<H, typename PopBack<Vector<T...>>::type>::type;
    };

    template <int T>
    struct PopBack<Vector<T>>
    {
        using type = Vector<>;
    };

    static_assert(std::is_same_v<PopBack<Vector<1, 2, 3, 4>>::type, Vector<1, 2, 3>>);

    /**
     * 7. Define RemoveFirst, that removes the first occurence of element R from vector V.
     */

    template <int N, typename V>
    struct RemoveFirst;

    template <int N, int H, int... T>
    struct RemoveFirst<N, Vector<H, T...>>
    {
        using type = typename Prepend<H, typename RemoveFirst<N, Vector<T...>>::type>::type;
    };

    template <int N, int... T>
    struct RemoveFirst<N, Vector<N, T...>>
    {
        using type = Vector<T...>;
    };

    template <int N, int... T>
    struct RemoveFirst<N, Vector<T...>>
    {
        using type = Vector<T...>;
    };

    static_assert(std::is_same_v<RemoveFirst<1, Vector<1, 1, 2>>::type, Vector<1, 2>>);

    /**
     * 8. Define RemoveAll, that removes all occurences of element R from vector V.
     */

    template <int N, typename V>
    struct RemoveAll;

    template <int N, int H, int... T>
    struct RemoveAll<N, Vector<H, T...>>
    {
        using type = typename Prepend<H, typename RemoveAll<N, Vector<T...>>::type>::type;
    };

    template <int N, int... T>
    struct RemoveAll<N, Vector<N, T...>>
    {
        using type = typename RemoveAll<N, Vector<T...>>::type;
    };

    template <int N, int... T>
    struct RemoveAll<N, Vector<T...>>
    {
        using type = Vector<T...>;
    };

    template <int N>
    struct RemoveAll<N, Vector<N>>
    {
        using type = Vector<>;
    };

    static_assert(std::is_same_v<RemoveAll<9, Vector<1, 9, 2, 9, 3, 9>>::type, Vector<1, 2, 3>>);

    /**
     * 9. Define Length.
     * Hint: Use `static constexpr int value = ...` inside the struct.
     */

    template <typename T>
    struct Length;

    template <int H, int... T>
    struct Length<Vector<H, T...>>
    {
        static constexpr int value = Length<Vector<T...>>::value + 1;
    };

    template <>
    struct Length<Vector<>>
    {
        static constexpr int value = 0;
    };

    static_assert(Length<Vector<1, 2, 3>>::value == 3);

    /**
     * 10. Define length, which works like Length<V>::value.
     * Hint: See how is_same_v is defined in terms of is_same.
     */

    template <typename T>
    inline constexpr std::size_t length = Length<T>::value;

    static_assert(length<Vector<>> == 0);
    static_assert(length<Vector<1, 2, 3>> == 3);

    /**
     * 11. Define Min, that stores the minimum of a vector in its property `value`.
     */

    template <int M, typename T>
    struct Min_;

    template <int M, int H, int... T>
    struct Min_<M, Vector<H, T...>>
    {
        static constexpr int value = M < Min_<H, Vector<T...>>::value ? M : Min_<H, Vector<T...>>::value;
    };

    template <int M, int H>
    struct Min_<M, Vector<H>>
    {
        static constexpr int value = M < H ? M : H;
    };

    template <typename T>
    struct Min;

    template <int H>
    struct Min<Vector<H>>
    {
        static constexpr int value = H;
    };

    template <int H, int... T>
    struct Min<Vector<H, T...>>
    {
        static constexpr int value = Min_<H, Vector<T...>>::value;
    };

    static_assert(Min<Vector<3, 1, 2>>::value == 1);
    static_assert(Min<Vector<1, 2, 3>>::value == 1);
    static_assert(Min<Vector<3, 2, 1>>::value == 1);

    /**
     * 12. Define Sort.
     */

    template <typename T>
    struct Sort;

    template <int... T>
    struct Sort<Vector<T...>>
    {
        static constexpr int min = Min<Vector<T...>>::value;
        using type = typename Prepend<min, typename Sort<typename RemoveFirst<min, Vector<T...>>::type>::type>::type;
    };

    template <int H>
    struct Sort<Vector<H>>
    {
        using type = Vector<H>;
    };

    static_assert(std::is_same_v<Sort<Vector<4, 1, 2, 5, 6, 3>>::type, Vector<1, 2, 3, 4, 5, 6>>);
    static_assert(std::is_same_v<Sort<Vector<3, 3, 1, 1, 2, 2>>::type, Vector<1, 1, 2, 2, 3, 3>>);
    static_assert(std::is_same_v<Sort<Vector<2, 2, 1, 1, 3, 3>>::type, Vector<1, 1, 2, 2, 3, 3>>);

    /**
     * 13. Define Uniq.
     */

    template <typename T>
    struct Uniq;

    template <int H, int HH, int... T>
    struct Uniq<Vector<H, HH, T...>>
    {
        using type =
    };

    // static_assert(std::is_same_v<Uniq<Vector<1,1,2,2,1,1>>::type, Vector<1,2,1>>);

    /**
     * 14. Define type Set.
     */

    // Your code goes here:
    // ^ Your code goes here

    // static_assert(std::is_same_v<Set<2,1,3,1,2,3>::type, Set<1,2,3>::type>);

    /**
     * 15. Define SetFrom.
     */

    // Your code goes here:
    // ^ Your code goes here

    // static_assert(std::is_same_v<SetFrom<Vector<2,1,3,1,2,3>>::type, Set<1,2,3>::type>);

    /**
     * 16. Define Get for Vector.
     * Provide an improved error message when accessing outside of Vector bounds.
     */

    // Your code goes here:
    // ^ Your code goes here

    // static_assert(Get<0, Vector<0,1,2>>::value == 0);
    // static_assert(Get<1, Vector<0,1,2>>::value == 1);
    // static_assert(Get<2, Vector<0,1,2>>::value == 2);
    // static_assert(Get<9, Vector<0,1,2>>::value == 2); // How good is your error message?

    /**
     * 17. Define BisectLeft for Vector.
     * Given n and arr, return the first index i such that arr[i] >= n.
     * If it doesn't exist, return the length of the array.
     *
     * Don't worry about complexity but aim for the binary search pattern.
     *
     * Hint: You might find it convenient to define a constexpr helper function.
     */

    // Your code goes here:
    // ^ Your code goes here

    // static_assert(BisectLeft<  3, Vector<0,1,2,3,4>>::value == 3);
    // static_assert(BisectLeft<  3, Vector<0,1,2,4,5>>::value == 3);
    // static_assert(BisectLeft<  9, Vector<0,1,2,4,5>>::value == 5);
    // static_assert(BisectLeft< -1, Vector<0,1,2,4,5>>::value == 0);
    // static_assert(BisectLeft<  2, Vector<0,2,2,2,2,2>>::value == 1);

    /**
     * 18. Define Insert for Vector, it should take position, value and vector.
     * Don't worry about bounds.
     * Hint: use the enable_if trick, e.g.
     *   template<typename X, typename Enable = void> struct Foo;
     *   template<typename X> struct<std::enable_if_t<..something      about X..>> Foo {...};
     *   template<typename X> struct<std::enable_if_t<..something else about X..>> Foo {...};
     */

    // Your code goes here:
    // ^ Your code goes here

    // static_assert(std::is_same_v<Insert<0, 3, Vector<4,5,6>>::type, Vector<3,4,5,6>>);
    // static_assert(std::is_same_v<Insert<1, 3, Vector<4,5,6>>::type, Vector<4,3,5,6>>);
    // static_assert(std::is_same_v<Insert<2, 3, Vector<4,5,6>>::type, Vector<4,5,3,6>>);
    // static_assert(std::is_same_v<Insert<3, 3, Vector<4,5,6>>::type, Vector<4,5,6,3>>);

}

int main()
{
    print(Vector<>{});
    print(Vector<1>{});
    print(Vector<1, 2, 3, 4, 5, 6>{});
    std::cout << typeid(Vector<1, 2, 3, 4, 5, 6>{}).name() << '\n';
}