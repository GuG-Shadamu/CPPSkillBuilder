/*
 * @Author: Tairan Gao
 * @Date:   2023-12-11 02:54:20
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-12-11 02:58:18
 */
#include <iostream>

template <int N>
struct Pow10
{
    static constexpr unsigned long long value = 10 * Pow10<N - 1>::value;
};

template <>
struct Pow10<0>
{
    static constexpr unsigned long long value = 1;
};

template <int Y, int Precision,
          unsigned long long InfX = 0,
          unsigned long long SupX = ((Y == 1) ? 1 : static_cast<unsigned long long>(Y) * Pow10<Precision>::value * Pow10<Precision>::value / 2),
          bool Done = ((SupX - InfX) <= 1 ? true : ((SupX * SupX <= static_cast<unsigned long long>(Y) * Pow10<Precision>::value * Pow10<Precision>::value) && ((SupX + 1) * (SupX + 1) > static_cast<unsigned long long>(Y) * Pow10<Precision>::value * Pow10<Precision>::value)))>
struct meta_sqrt
{
    static constexpr unsigned long long MidX = (InfX + SupX) / 2;
    static constexpr bool TakeInf = MidX * MidX > static_cast<unsigned long long>(Y) * Pow10<Precision>::value *Pow10<Precision>::value;
    static constexpr unsigned long long NewInf = TakeInf ? InfX : MidX;
    static constexpr unsigned long long NewSup = TakeInf ? MidX : SupX;
    static constexpr int value = meta_sqrt<Y, Precision, NewInf, NewSup>::value;
};

template <int Y, int Precision, unsigned long long InfX, unsigned long long SupX>
struct meta_sqrt<Y, Precision, InfX, SupX, true>
{
    static constexpr int value = (SupX * SupX <= static_cast<unsigned long long>(Y) * Pow10<Precision>::value * Pow10<Precision>::value) ? static_cast<int>(SupX) : static_cast<int>(InfX);
};

int main()
{
    static constexpr int x = 42;
    static constexpr int precision = 5;                                                                // 5 decimal places (max)
    std::cout << meta_sqrt<x, precision>::value / static_cast<float>(Pow10<precision>::value) << "\n"; // 6.48074
}
