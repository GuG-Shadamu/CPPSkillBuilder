# -*- coding: utf-8 -*-
# @Author: Tairan Gao
# @Date:   2023-09-08 11:23:45
# @Last Modified by:   Tairan Gao
# @Last Modified time: 2023-09-08 11:29:18

import sys


def minimumProcessingTime(n, processorTime, taskTime):
    processorTime.sort()
    taskTime.sort()

    res = sys.maxsize
    for i in range(3, len(taskTime)):
        temp = 0
        for pt in processorTime:
            temp = max(taskTime[i] + pt, temp)
        res = min(res, temp)

    return res


if __name__ == "__main__":
    sol = minimumProcessingTime(2, [10, 20], [2, 3, 1, 2, 5, 8, 4, 3])
    print(sol)
