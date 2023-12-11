/*
 * @Author: Tairan Gao
 * @Date:   2023-12-11 02:54:20
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-12-11 02:56:23
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
class meta_sqrt
{
    static constexpr unsigned long long MidX = (InfX + SupX) / 2;
    static constexpr bool TakeInf = MidX * MidX > static_cast<unsigned long long>(Y) * Pow10<Precision>::value *Pow10<Precision>::value;
    static constexpr unsigned long long NewInf = TakeInf ? InfX : MidX;
    static constexpr unsigned long long NewSup = TakeInf ? MidX : SupX;

public:
    static constexpr int ret = meta_sqrt<Y, Precision, NewInf, NewSup>::ret;
};

template <int Y, int Precision, unsigned long long InfX, unsigned long long SupX>
class meta_sqrt<Y, Precision, InfX, SupX, true>
{
public:
    static constexpr int ret = (SupX * SupX <= static_cast<unsigned long long>(Y) * Pow10<Precision>::value * Pow10<Precision>::value) ? static_cast<int>(SupX) : static_cast<int>(InfX);
};

int main()
{
    static constexpr int x = 42;
    static constexpr int precision = 5;                                                              // 5 decimal places (max)
    std::cout << meta_sqrt<x, precision>::ret / static_cast<float>(Pow10<precision>::value) << "\n"; // 6.48074
}
