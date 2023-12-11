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

// Internal helper template
template <int Y, int Precision, unsigned long long InfX, unsigned long long SupX, bool Done>
struct meta_sqrt_internal
{
    static constexpr unsigned long long MidX = (InfX + SupX) / 2;
    static constexpr bool TakeInf = MidX * MidX > static_cast<unsigned long long>(Y) * Pow10<Precision>::value *Pow10<Precision>::value;
    static constexpr unsigned long long NewInf = TakeInf ? InfX : MidX;
    static constexpr unsigned long long NewSup = TakeInf ? MidX : SupX;
    static constexpr int value = meta_sqrt_internal < Y, Precision, NewInf, NewSup, NewInf == NewSup || NewSup - NewInf == 1 > ::value;
};

template <int Y, int Precision, unsigned long long InfX, unsigned long long SupX>
struct meta_sqrt_internal<Y, Precision, InfX, SupX, true>
{
    static constexpr int value = (SupX * SupX <= static_cast<unsigned long long>(Y) * Pow10<Precision>::value * Pow10<Precision>::value) ? static_cast<int>(SupX) : static_cast<int>(InfX);
};

// User-facing template
template <int Y, int Precision>
struct meta_sqrt
{
    static constexpr int value = meta_sqrt_internal < Y, Precision, 0, (Y == 1) ? 1 : static_cast<unsigned long long>(Y) * Pow10<Precision>::value, false > ::value;
};

int main()
{
    static constexpr int x = 42;
    static constexpr int precision = 3;                                                                // 5 decimal places (max)
    std::cout << meta_sqrt<x, precision>::value / static_cast<float>(Pow10<precision>::value) << "\n"; // 6.48074
}
