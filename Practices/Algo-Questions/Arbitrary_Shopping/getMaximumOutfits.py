# -*- coding: utf-8 -*-
# @Author: Tairan Gao
# @Date:   2023-11-30 15:10:31
# @Last Modified by:   Tairan Gao
# @Last Modified time: 2023-11-30 16:10:30


def getMaxOutfits(n, outfits, money):
    res = 0
    cur_num = 0
    cur_sum = 0

    start = 0

    for i in range(n):
        cur_sum += outfits[i]
        cur_num += 1

        while cur_sum > money:
            cur_sum -= outfits[start]
            cur_num -= 1
            start += 1
            if start > i:
                return res

        res = max(cur_num, res)

    return res


outfits = [2, 3, 5, 1, 1, 2, 1]
money = 5
n = 7

print(getMaxOutfits(n, outfits, money))
