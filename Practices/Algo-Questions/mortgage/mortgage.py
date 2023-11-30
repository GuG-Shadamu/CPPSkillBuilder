# -*- coding: utf-8 -*-
# @Author: Tairan Gao
# @Date:   2023-11-30 11:46:01
# @Last Modified by:   Tairan Gao
# @Last Modified time: 2023-11-30 12:13:18

from typing import List


def countMaximumDays(lend: List[int], payback: List[int]) -> int:
    order = [i[0] for i in sorted(enumerate(payback), key=lambda x: x[1])]

    days = 0
    need_to_payback = 0
    for i in order:
        borrowed = lend[i]
        if borrowed >= need_to_payback:
            days += 1
        else:
            continue

        need_to_payback = payback[i]

    return days


if __name__ == "__main__":
    # lend = [4, 6, 1, 8]
    # payback = [7, 10, 3, 9]

    # Test Case 1
    print(countMaximumDays([5, 3, 4, 2], [6, 4, 7, 3]))  # Expected Output: 3

    # Test Case 2
    print(countMaximumDays([2, 5, 1, 3], [3, 6, 2, 4]))  # Expected Output: 4

    # Test Case 3
    print(countMaximumDays([7, 8, 5], [10, 9, 6]))  # Expected Output: 2

    # Test Case 4
    print(countMaximumDays([1, 2, 3, 4], [2, 3, 4, 5]))  # Expected Output: 4

    # Test Case 5
    print(countMaximumDays([10, 5, 3], [15, 7, 4]))  # Expected Output: 1
