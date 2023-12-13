
# Question

You are given a positive integer N. Your task is to find the smallest integer greater than N that does not contain two identical consecutive digits.

### Example
Given N = 1765, the smallest integer greater than N is 1766. 

However, in 1766 the las two digits are identical. The next integer, 1767, does not contain two identical consecutive digits, a is the smallest integer greater than 1765 that fulfils the condition. 

Note that the second and fourth digits in 1767 can both be 7 as they are not consecutive.

### Task

Write a function:
def solution (X)
that, given an integer N, returns the smallest integer greater than N that does not contain two identical consecutive digits.