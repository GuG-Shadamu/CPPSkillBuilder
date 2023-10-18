/*
 * @Author: Tairan Gao
 * @Date:   2023-10-16 17:37:27
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-10-18 18:09:52
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

    template <template <int...> class Container, int... T>
    void print(Container<T...>) // empty vector case
    {
        std::cout << std::endl;
    }

    template <template <int...> class Container, int H>
    void print(Container<H>)
    {
        std::cout << H << std::endl;
    }

    template <template <int...> class Container, int H, int... T>
    void print(Container<H, T...>)
    {
        std::cout << H << " ";
        print(Container<T...>{});
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
    static_assert(std::is_same_v<Prepend<1, Vector<>>::type, Vector<1>>);

    /**
     * 4. Define PrependT that can be used without ::type.
     * Hint: See how enable_if_t is defined in terms of enable_if.
     *
     * This technique is not used further to reduce boilerplate.
     */

    template <int H, typename V>
    using Prepend_t = typename Prepend<H, V>::type;

    static_assert(std::is_same_v<Prepend_t<1, Vector<2, 3>>, Vector<1, 2, 3>>);
    static_assert(std::is_same_v<Prepend_t<1, Vector<>>, Vector<1>>);

    /**
     * 5. Define Append.
     */

    template <int H, typename V>
    struct Append;

    template <int H, typename V>
    using Append_t = typename Append<H, V>::type;

    template <int N, int H, int... T>
    struct Append<N, Vector<H, T...>>
    {
        using type = Prepend_t<H, Append_t<N, Vector<T...>>>;
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

    template <typename V>
    using PopBack_t = typename PopBack<V>::type;

    template <int H, int... T>
    struct PopBack<Vector<H, T...>>
    {
        using type = Prepend_t<H, PopBack_t<Vector<T...>>>;
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

    template <int N, typename V>
    using RemoveFirst_t = typename RemoveFirst<N, V>::type;

    template <int N, template <int...> class Container, int... Ints>
    struct RemoveFirst<N, Container<Ints...>>
    {
        using type = Container<Ints...>;
    };

    template <int N, template <int...> class Container, int H, int... T>
    struct RemoveFirst<N, Container<H, T...>>
    {
        using type = Prepend_t<H, RemoveFirst_t<N, Container<T...>>>;
    };

    template <int N, template <int...> class Container, int... T>
    struct RemoveFirst<N, Container<N, T...>>
    {
        using type = Container<T...>;
    };

    static_assert(std::is_same_v<RemoveFirst<1, Vector<1, 1, 2>>::type, Vector<1, 2>>);
    static_assert(std::is_same_v<RemoveFirst<1, Vector<1>>::type, Vector<>>);

    /**
     * 8. Define RemoveAll, that removes all occurences of element R from vector V.
     */

    template <int N, typename V>
    struct RemoveAll;

    template <int N, typename V>
    using RemoveAll_t = typename RemoveAll<N, V>::type;

    template <int N, template <int...> class Container>
    struct RemoveAll<N, Container<>>
    {
        using type = Container<>;
    };

    template <int N, template <int... INTS> class Container, int H, int... T>
    struct RemoveAll<N, Container<H, T...>>
    {
        using type = Prepend_t<H, RemoveAll_t<N, Container<T...>>>;
    };

    template <int N, template <int... INTS> class Container, int... T>
    struct RemoveAll<N, Container<N, T...>>
    {
        using type = RemoveAll_t<N, Container<T...>>;
    };

    static_assert(std::is_same_v<RemoveAll<9, Vector<1, 9, 2, 9, 3, 9>>::type, Vector<1, 2, 3>>);
    static_assert(std::is_same_v<RemoveAll<9, Vector<9, 9, 9>>::type, Vector<>>);
    /**
     * 9. Define Length.
     * Hint: Use `static constexpr int value = ...` inside the struct.
     */

    template <typename T>
    struct Length;

    template <template <int...> class Container, int H, int... T>
    struct Length<Container<H, T...>>
    {
        static constexpr int value = Length<Container<T...>>::value + 1;
    };

    template <template <int...> class Container>
    struct Length<Container<>>
    {
        static constexpr int value = 0;
    };

    static_assert(Length<Vector<1, 2, 3>>::value == 3);
    static_assert(Length<Vector<>>::value == 0);

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

    template <int M, template <int...> class Container, int H, int... T>
    struct Min_<M, Container<H, T...>>
    {
        static constexpr int value = M < H ? Min_<M, Container<T...>>::value : Min_<H, Container<T...>>::value;
    };

    template <int M, template <int...> class Container>
    struct Min_<M, Container<>>
    {
        static constexpr int value = M;
    };

    template <typename T>
    struct Min;

    template <template <int H> class Container, int H>
    struct Min<Container<H>>
    {
        static constexpr int value = H;
    };

    template <template <int...> class Container, int H, int... T>
    struct Min<Container<H, T...>>
    {
        static constexpr int value = Min_<H, Container<T...>>::value;
    };

    static_assert(Min<Vector<3, 1, 2>>::value == 1);
    static_assert(Min<Vector<1, 2, 3>>::value == 1);
    static_assert(Min<Vector<3, 2, 1>>::value == 1);

    /**
     * 12. Define Sort.
     */

    // Forward declaration
    // Forward declaration
    template <typename T>
    struct Sort;

    template <typename T>
    using Sort_t = typename Sort<T>::type;

    // General case
    template <template <int...> class Container, int First, int... Rest>
    struct Sort<Container<First, Rest...>>
    {
        static constexpr int min = Min<Container<First, Rest...>>::value;
        using removed_type = RemoveFirst_t<min, Container<First, Rest...>>;
        using type = Prepend_t<min, Sort_t<removed_type>>;
    };

    // Base case for an empty container
    template <template <int...> class Container>
    struct Sort<Container<>>
    {
        using type = Container<>;
    };

    static_assert(std::is_same_v<Sort<Vector<4, 1, 2, 5, 6, 3>>::type, Vector<1, 2, 3, 4, 5, 6>>);
    static_assert(std::is_same_v<Sort<Vector<3, 3, 1, 1, 2, 2>>::type, Vector<1, 1, 2, 2, 3, 3>>);
    static_assert(std::is_same_v<Sort<Vector<2, 2, 1, 1, 3, 3>>::type, Vector<1, 1, 2, 2, 3, 3>>);

    /**
     * 13. Define Uniq.
     */

    template <typename T>
    struct Uniq;

    template <typename T>
    using Uniq_t = typename Uniq<T>::type;

    template <template <int...> class Container, int... T>
    struct Uniq<Container<T...>>
    {
        using type = Container<T...>;
    };

    template <template <int...> class Container, int H, int... T>
    struct Uniq<Container<H, H, T...>>
    {
        using type = Prepend_t<H, Uniq_t<Container<T...>>>;
    };

    static_assert(std::is_same_v<Uniq<Vector<1, 1, 2, 2, 1, 1>>::type, Vector<1, 2, 1>>);

    /**
     * 14. Define type Set.
     */

    template <int... T>
    struct Set
    {
        using type = typename Uniq<typename Sort<Vector<T...>>::type>::type;
    };
    /**
     * 15. Define SetFrom.
     */

    template <typename T>
    struct SetFrom;

    template <int H, int HH, int... T>
    struct SetFrom<Vector<H, HH, T...>>
    {
        using type = typename Sort<
            typename Prepend<
                H, typename SetFrom<
                       typename RemoveAll<
                           H, Vector<HH, T...>>::type>::type>::type>::type;
    };

    template <int... T>
    struct SetFrom<Vector<T...>>
    {
        using type = Vector<T...>;
    };

    static_assert(std::is_same_v<SetFrom<Vector<2, 1, 3, 1, 2, 3>>::type, Set<1, 2, 3>::type>);

    /**
     * 16. Define Get for Vector.
     * Provide an improved error message when accessing outside of Vector bounds.
     */

    template <int G, typename T>
    struct Get;

    template <int H, int... T>
    struct Get<0, Vector<H, T...>>
    {
        static constexpr int value = H;
    };

    template <int G, int H, int... T>
    struct Get<G, Vector<H, T...>>
    {
        static_assert(G >= 0, "Access out of bounds.");
        static constexpr int len = Length<Vector<H, T...>>::value;
        static_assert(G < len, "Access out of bounds.");
        static constexpr int value =
            Get<G - 1, Vector<T...>>::value;
    };

    static_assert(Get<0, Vector<0, 1, 2>>::value == 0);
    static_assert(Get<1, Vector<0, 1, 2>>::value == 1);
    static_assert(Get<2, Vector<0, 1, 2>>::value == 2);
    // static_assert(Get<9, Vector<0, 1, 2>>::value == 2); // How good is your error message?

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

    print(Set<1>{});
    print(Set<1, 2>{});
    print(Set<1, 1, 2>{});

    std::cout << typeid(Vector<1, 2, 3, 4, 5, 6>{}).name() << '\n';
}