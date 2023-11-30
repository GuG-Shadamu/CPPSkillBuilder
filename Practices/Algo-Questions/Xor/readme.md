# Xor

A new circuit is developed which takes three inputs \( A \), \( B \), and \( N \). The task is to find the output of the circuit which is as follows: an integer \( X \) such that \( X < 2^N \), and the product of \( (A \oplus X) \) and \( (B \oplus X) \) is maximum.

Since the output can be large, return it modulo \( 10^9 + 7 \).

**Note:** \( \oplus \) is the bitwise Xor Operator.

Consider the following example,

\( A = 4 \)

\( B = 6 \)

\( N = 3 \)

We can choose \( X = 3 \) and \( (A \oplus X) = 7 \), \( (B \oplus X) = 5 \).

The product is 35 and it can be shown that it is maximum

# Function Description
Complete the function `xorMultiplication` in the editor below. The function must return an integer denoting the maximum product modulo \( 10^9 + 7 \).

`xorMultiplication` has the following parameter(s):
- \( A \): an integer
- \( B \): an integer
- \( N \): an integer

# Constraints

- \( 0 \leq N \leq 30 \)
- \( 1 \leq A < 2^N \)
- \( 1 \leq B < 2^N \)
