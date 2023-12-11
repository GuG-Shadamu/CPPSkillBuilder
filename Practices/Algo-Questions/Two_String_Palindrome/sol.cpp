/*
 * @Author: Tairan Gao
 * @Date:   2023-12-09 15:50:54
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-12-09 16:45:48
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

std::array<int, 26> get_book(const std::string &input)
{
    std::vector<std::string> res;
    std::array<int, 26> book{0};
    for (const auto &c : input)
    {
        book[c - 'a'] += 1;
    }
    return book;
}

std::string get_palindrome(const std::array<int, 26> &book, bool first = true)
{
    bool mid_select = false;
    char mid;
    int num;
    std::string upper_string{""};
    std::string res;
    for (size_t i = 0; i < 26; i++)
    {
        if (book[i] % 2 != 0)
        {
            if (!mid_select)
            {
                mid = 'a' + i;
                mid_select = true;
            }
        }
        if (book[i] >= 2)
        {
            num = book[i] / 2;
            for (size_t j = 0; j < num; j++)
            {
                upper_string += ('a' + i);
            }
        }
    }
    if (!first)
    {
        std::reverse(upper_string.begin(), upper_string.end());
    }
    res += upper_string;
    if (mid_select)
    {
        res += mid;
    }
    std::reverse(upper_string.begin(), upper_string.end());
    res += upper_string;
    return res;
}

std::string sol(const std::string &a, const std::string &b)
{
    auto a_book = get_book(a);
    auto b_book = get_book(b);
    std::string a_p = get_palindrome(a_book, true);
    std::string b_p = get_palindrome(b_book, false);
    auto a_p_book = get_book(a_p);
    auto b_p_book = get_book(b_p);
    std::array<int, 26> book{0};

    if (a_p.size() % 2 != 0 && b_p.size() % 2 != 0)
    {
        b_p_book[b_p[b_p.size() / 2] - 'a'] -= 1;
    }

    for (size_t i = 0; i < 26; i++)
    {
        book[i] = a_p_book[i] + b_p_book[i];
    }
    return get_palindrome(book, true);
}

int main()
{
    std::string a{"aaab"};
    std::string b{"ccca"};
    std::cout << sol(a, b) << "\n";
    return 0;
}