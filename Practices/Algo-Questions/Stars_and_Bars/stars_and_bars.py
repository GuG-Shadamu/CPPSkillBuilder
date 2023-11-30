# -*- coding: utf-8 -*-
# @Author: Tairan Gao
# @Date:   2023-11-30 10:45:37
# @Last Modified by:   Tairan Gao
# @Last Modified time: 2023-11-30 11:17:32

from typing import List


def stars_and_bars(s: str, startIndex: List[int], endIndex: List[int]) -> List[int]:
    n = len(s)
    dp = [0 for i in range(n + 1)]

    skip = True
    cur = 0
    for i in range(1, n):
        c = s[i - 1]
        if skip and c != "|":
            continue

        skip = False
        if c == "|":
            dp[i] = dp[i - 1] + cur
            cur = 0
        else:
            cur += 1
            dp[i] = dp[i - 1]

    print(dp)
    sol = []
    for i in range(len(startIndex)):
        start = startIndex[i]
        end = endIndex[i]
        sol.append(dp[end] - dp[start])

    return sol


if __name__ == "__main__":
    s = "|**|*|*"
    startIndex = [1, 1]
    endIndex = [5, 6]
    sol = stars_and_bars(s, startIndex, endIndex)
    print(sol)
