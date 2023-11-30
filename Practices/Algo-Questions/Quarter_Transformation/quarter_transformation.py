# -*- coding: utf-8 -*-
# @Author: Tairan Gao
# @Date:   2023-11-30 12:16:24
# @Last Modified by:   Tairan Gao
# @Last Modified time: 2023-11-30 12:22:42

from typing import List


def quarter_transformation(inputs: List[str]) -> List[str]:
    sol = []
    for input in inputs:
        tokens = input.split("-")
        year = tokens[0]
        month = int(tokens[1])
        quarter = (month - 1) // 3 + 1
        sol.append(year + "Q" + str(quarter))

    return sol


inputs = ["2014-03-25", "2012-08-05"]
print(quarter_transformation(inputs))
