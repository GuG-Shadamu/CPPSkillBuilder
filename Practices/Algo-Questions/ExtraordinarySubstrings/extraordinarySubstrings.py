# -*- coding: utf-8 -*-
# @Author: Tairan Gao
# @Date:   2023-09-08 13:16:23
# @Last Modified by:   Tairan Gao
# @Last Modified time: 2023-09-08 13:25:04


keyMap = {
    "a": 1,
    "b": 1,
    "c": 2,
    "d": 2,
    "e": 2,
    "f": 3,
    "g": 3,
    "h": 3,
    "i": 4,
    "j": 4,
    "k": 4,
    "l": 5,
    "m": 5,
    "n": 5,
    "o": 6,
    "p": 6,
    "q": 6,
    "r": 6,
    "s": 7,
    "t": 7,
    "u": 7,
    "v": 8,
    "w": 8,
    "x": 9,
    "y": 9,
    "z": 9,
}


def isExtraordinary(input):
    n = len(input)
    sum = 0
    for c in input:
        sum += keyMap[c]

    return sum % n == 0


def extraordinarySubstring(input):
    n = len(input)
    res = n

    for i in range(2, n + 1):
        for j in range(n - i + 1):
            if isExtraordinary(input[j : j + i]):
                res += 1

    return res


print(extraordinarySubstring("asdf"))
