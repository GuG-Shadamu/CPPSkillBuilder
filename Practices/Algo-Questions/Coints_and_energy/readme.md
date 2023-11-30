# 3. Coins and Energy

Alex will visit a number of houses that are arranged in a line. Each house has a number of coins and an amount of energy available. The journey must begin at the first house, and each house along the journey must be visited. None can be skipped over, but Alex can end the journey at any point. It costs 1 unit of energy to move from one house to the next. Alex can collect either the energy or the coins when visiting a house. Determine the maximum number of coins Alex can collect while never having a negative energy amount.

## Example

`n = 3`
`initialEnergy = 0`
`energy = [2, 1, 1]`
`coins = [1, 5, 7]`

There are `n` houses in a line. The `j^th` house has `energy[j]` energy and `coins[j]` coins. Alex starts the journey at the first house with `initialEnergy` energy.

The best approach is to collect 2 units of energy at the first house, then `5 + 7 = 12` coins at the second and third houses. Alex's energy level is `0` after moving to the second and third houses.

## Function Description

Complete the function `getRich` in the editor below. The function must return an integer that represents the maximum number of coins that can be collected.

`getRich` has the following parameter(s):

- `initialEnergy`: long integer
- `energy [energy[0],...,energy[n-1]]`: an array of integers
- `coins [coins[0],...,coins[n-1]]`: an array of integers

## Constraints

- `1 ≤ n ≤ 1000`
- `0 ≤ initialEnergy ≤ 10^14`
- `0 ≤ energy[j], coins[j] ≤ 10^3`
