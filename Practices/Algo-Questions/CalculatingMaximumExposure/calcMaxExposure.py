# -*- coding: utf-8 -*-
# @Author: Tairan Gao
# @Date:   2023-09-08 13:58:12
# @Last Modified by:   Tairan Gao
# @Last Modified time: 2023-09-08 14:14:40


def calcMaxExposure(inputs):
    timestamps = []
    exposureMap = {}

    for input in inputs:
        tokens = input.split(" ")
        entry = int(tokens[3])
        exit = int(tokens[4])

        if int(entry) not in exposureMap:
            exposureMap[entry] = 0
            timestamps.append(entry)

        if int(exit) not in exposureMap:
            exposureMap[exit] = 0
            timestamps.append(exit)

        exposureMap[entry] += int(tokens[0]) * int(tokens[2])
        exposureMap[exit] -= int(tokens[0]) * int(tokens[2])

    timestamps.sort()

    exposure = 0
    res = 0
    for time in timestamps:
        exposure += exposureMap[time]
        res = max(res, exposure)

    return res


inputs = ["200 APPL 151 1010 1135", "100 GNED 65 855 1020", "200 META 195 845 1030"]

print(calcMaxExposure(inputs))
