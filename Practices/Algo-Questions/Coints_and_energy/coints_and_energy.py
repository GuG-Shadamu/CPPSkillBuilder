# -*- coding: utf-8 -*-
# @Author: Tairan Gao
# @Date:   2023-11-30 12:54:05
# @Last Modified by:   Tairan Gao
# @Last Modified time: 2023-11-30 14:34:17

from typing import List


class Solution:
    def getRich(
        self, n: int, initialEnergy: int, energies: List[int], coints: List[int]
    ) -> int:
        self.energies = energies
        self.n = n
        self.coints = coints
        self.visited = {}

        return self.helper(0, initialEnergy)

    def helper(self, i, cur_energy):
        if cur_energy < 0:
            return 0

        if i == self.n - 1:
            return self.coints[i]

        if (i, cur_energy) in self.visited:
            return self.visited[(i, cur_energy)]

        take_energy = self.helper(i + 1, cur_energy + self.energies[i] - 1)
        take_coin = self.helper(i + 1, cur_energy - 1) + self.coints[i]

        max_val = max(take_coin, take_energy)
        self.visited[(i, cur_energy)] = max_val

        return max_val


house_energy = [1, 5, 3, 3, 1]
house_coins = [3, 23, 9, 2, 2]

sol = Solution()
print(sol.getRich(5, 1, house_energy, house_coins))
