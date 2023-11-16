# -*- coding: utf-8 -*-
# @Author: Tairan Gao
# @Date:   2023-09-08 11:36:33
# @Last Modified by:   Tairan Gao
# @Last Modified time: 2023-09-08 11:41:31

from collections import Counter

n = 6
items = [4, 5, 6, 5, 4, 3]


freq_counter = Counter(items)
print(sorted(items, key=lambda x: (freq_counter[x], x)))
