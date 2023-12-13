/*
 * @Author: Tairan Gao
 * @Date:   2023-12-12 12:41:39
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-12-13 01:16:12
 */
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int findNextNumber(int N)
{
    std::vector<int> digits;
    while (N > 0)
    {
        digit.emplace_back(N % 10);
        N = N / 10;
    }

    return
}

int main()
{
    int N = 9999;

    int result = findNextNumber(N + 1); // Start with N + 1
    std::cout << "The next number without consecutive identical digits is: " << result << std::endl;

    return 0;
}
