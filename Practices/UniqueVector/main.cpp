/*
 * @Author: Tairan Gao
 * @Date:   2023-09-12 13:42:40
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-09-12 13:45:40
 */

#include <type_traits>
#include <cstdint>

template <std::int32_t... Is>
struct vector;
template <std::int32_t N, typename V>
struct vector_cat;
template <std::int32_t N, std::int32_t... Tail>

struct vector_cat<N, vector<Tail...>>
{
    using concat = vector<N, Tail...>;
};

template <>
struct vector<>
{
    using unique = vector<>;
};


template <std::int32_t N>
struct vector<N>
{
    using unique = vector<N>;
};

template <std::int32_t M, std::int32_t N, std::int32_t... Tail>
struct vector<M, N, Tail...>
{

    using unique = std::conditional_t<
        M == N, typename vector<M, Tail...>::unique,
        typename vector_cat<M, typename vector<N, Tail...>::unique>::concat>;
};

int main()
{
    using vec = vector<1, 5, 7, 3, 3, 9, 5, -2, 11, 3, 8, 8, 8, 42>;
    static_assert(
        std::is_same_v<typename vec::unique, vector<1, 5, 7, 3, 9, 5, -2, 11, 3, 8, 42>>);
}
