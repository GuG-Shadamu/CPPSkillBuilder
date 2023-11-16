# -*- coding: utf-8 -*-
# @Author: Tairan Gao
# @Date:   2023-09-08 12:05:41
# @Last Modified by:   Tairan Gao
# @Last Modified time: 2023-09-08 12:43:56

from collections import deque
import sys


def deliveryManagementSystem(start, n, roads):
    directions = [[] * n for i in range(n)]
    distances = [sys.maxsize] * n
    visited = set()
    queue = deque([(start - 1, 0)])
    max_distance = 0

    for road in roads:
        a, b = road
        directions[a - 1].append(b - 1)
        directions[b - 1].append(a - 1)

    while queue:
        node, distance = queue.popleft()
        max_distance = max(max_distance, distance)

        if node not in visited:
            visited.add(node)
        else:
            continue

        distances[node] = min(distances[node], distance)
        for neighbor in directions[node]:
            queue.append((neighbor, distance + 1))

    order_temp = [[] for i in range(max_distance + 1)]
    for i, v in enumerate(distances):
        order_temp[v].append(i)

    res = []
    for same_distance in order_temp[1:]:
        for node in same_distance:
            res.append(node + 1)
    print(res)


roads = [[1, 2], [2, 3], [2, 4]]
deliveryManagementSystem(1, 4, roads)
