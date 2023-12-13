# Find the size of Largest Subset with positive Bitwise AND
<https://www.geeksforgeeks.org/find-the-size-of-largest-subset-with-positive-bitwise-and/>

---

AND is a standard bitwise operation. For example, given `K = 12` (binary representation 01100) and `L=21` (binary representation 10101) we obtain:

`01100 AND 10101 = 00100`


The AND operation can be extended to N Integers, for example:

`01100 AND 10101 AND 00100 = 00100`

Because AND of 01100 (first argument) and 10101 (second argument) is 00100, and AND of this number with 00100 (third argument) is also 00100.


Write a function:
def solution (A)

that, given an array A consisting of N integers, returns the size of the largest possible subset of A such that AND of all its elements is greater than 0.

## Examples:

Given A-[13,7,2,8, 3] your function should return 3.
We can pick subset 13,7 and 3. AND of these elements is positive and it is the largest possible subset of numbers that fulfills the criteria.
