# Arbitrary Shopping


A shopper goes to a clothing store and picks an outfit. 
Later, the shopper buys all consecutive outfits starting with that outfit up to the nth outfit, as long as the money to pay for them is available. 
For example, after first selecting outfit i, the shopper will continue to purchase outfits i + 1, i + 2 and so on until there is not enough money to purchase another outfit. 
Determine the maximum number of outfits the shopper can buy.

## Example
    n = 7
    outfits = [2, 3, 5, 1, 1, 2, 1]
    money = 5

There are n = 7 outfits to choose from. There are three sub-arrays of prices that sum to less than or equal to money:
[2, 3], [5], [1, 1, 2, 1]. The longest of these, or the maximum number of outfits that can be bought, is 4.




## Constraints


- `1 ≤ n ≤ 10000`
- `1 ≤ outfits[i] ≤ 100`
- `1 ≤ money ≤ 10^6`