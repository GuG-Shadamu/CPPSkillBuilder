/*
 * @Author: Tairan Gao
 * @Date:   2023-11-30 11:18:07
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-11-30 11:44:29
 */

#include <vector>
#include <string>
#include <iostream>

auto stars_and_bars(std::string s, std::vector<int> startIndex, std::vector<int> endIndex) -> std::vector<int>
{
    bool skip = true;
    int n = s.size();
    auto dp = std::vector<int>(n + 1, 0);

    int cur = 0;

    for (int i = 1; i < n + 1; i++)
    {
        char c = s[i - 1];
        if (c != '|' && skip)
        {
            continue;
        }
        skip = false;

        if (c == '*')
        {
            dp[i] = dp[i - 1];
            cur += 1;
        }
        else // (c == '|')
        {
            dp[i] = dp[i - 1] + cur;
            cur = 0;
        }
    }
    int m = startIndex.size();
    std::vector<int> sol;
    for (int i = 0; i < m; i++)
    {
        int start = startIndex[i];
        int end = endIndex[i];
        sol.push_back(dp[end] - dp[start]);
    }
    return sol;
}

int main()
{
    auto s = "|**|*|*";

    auto startIndex = {1, 1};
    auto endIndex = {5, 6};

    auto sol = stars_and_bars(s, startIndex, endIndex);
    for (const auto &ele : sol)
    {
        std::cout << ele << "\n";
    }
    return 0;
}