# -*- coding: utf-8 -*-
# @Author: Tairan Gao
# @Date:   2023-11-30 12:25:06
# @Last Modified by:   Tairan Gao
# @Last Modified time: 2023-11-30 12:29:41
def xorMultiplication(A, B, N):
    # Find the highest bit where A and B differ.
    X = 0
    for i in range(N - 1, -1, -1):
        if ((A >> i) & 1) != ((B >> i) & 1):
            X = (1 << i) - 1
            break

    # Calculate the product of (A XOR X) and (B XOR X).
    product = (A ^ X) * (B ^ X)
    # Return the product modulo 10^9 + 7.
    return product % (10**9 + 7)


# Example
A = 4
B = 6
N = 3
print(xorMultiplication(A, B, N))  # Should return 35
