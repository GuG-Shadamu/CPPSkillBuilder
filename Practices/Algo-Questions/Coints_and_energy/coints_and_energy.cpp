/*
 * @Author: Tairan Gao
 * @Date:   2023-11-30 14:34:57
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-11-30 15:08:07
 */
#include <vector>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <algorithm>

int helper(int i, int n, int cur_energy, std::vector<int> &energies, std::vector<int> &coints, std::unordered_map<int, std::unordered_map<int, int>> &cache)
{
    if (cur_energy < 0)
    {
        return 0;
    }
    if (i == n - 1)
    {
        return coints[i];
    }

    auto it1 = cache.find(i);
    if (it1 != cache.end())
    {
        auto it2 = it1->second.find(cur_energy);
        if (it2 != it1->second.end())
        {
            return it2->second;
        }
    }
    else
    {
        cache[i] = std::unordered_map<int, int>();
    }
    int pick_coin = helper(i + 1, n, cur_energy - 1, energies, coints, cache) + coints[i];
    int pick_energy = helper(i + 1, n, cur_energy - 1 + energies[i], energies, coints, cache);
    int max_coin = std::max(pick_coin, pick_energy);
    cache[i][cur_energy] = max_coin;
    return max_coin;
}

int getRich(int n, int initialEnergy, std::vector<int> &energies, std::vector<int> &coints)
{
    auto cache = std::unordered_map<int, std::unordered_map<int, int>>{};
    return helper(0, n, initialEnergy, energies, coints, cache);
}

int main()
{
    std::vector<int> house_energy = {1, 5, 3, 3, 1};
    std::vector<int> house_coints = {3, 23, 9, 2, 2};
    std::cout << getRich(5, 1, house_energy, house_coints) << "\n";
}