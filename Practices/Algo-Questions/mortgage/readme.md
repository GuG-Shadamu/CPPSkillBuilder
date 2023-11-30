## Mortgage

There are *n* lenders who lend money, where each lender can lend only once and money can be borrowed from only one lender each day. Lender *i* lends `lend[i]` money to a borrower on the *j*th day, then `payback[i]` is returned to the lender on the (*j* + 1)th day in order to maintain a good credit score. Failure to do so results in a *default*. Initially, the borrower has no money. The borrower gets the money from a new lender each day, repays the previous loan, and spends the leftover money. At the end of each day, the borrower has no money left.

Find the maximum number of days the borrower can survive without having to incur a *default* if money is borrowed from lenders optimally.

### Example

There are *n* = 4 lenders, the money lent is `lend = [4, 6, 1, 8]`, and payback amounts are `payback = [7, 10, 3, 9]`.

An optimal order to borrow money is shown.

- Day 1: Borrow 1 unit from the 3rd lender and spend the 1 unit. Expected payback = 3.
- Day 2: Borrow 4 units from the 1st lender (4 units). Repay the 3 units and spend the remaining 1 unit. Expected payback = 7.
- Day 3: Borrow money from the 4th lender (8 units). Repay 7 units and spend the remaining 1 unit. Expected payback = 9.
- Day 4: Borrow money from the 2nd lender (6 units). The previous loan cannot be repaid and the borrower incurs a *default*.

Return 3. No other strategy leads to an answer greater than 3.

### Function Description

Complete the function `countMaximumDays` in the editor below.

`countMaximumDays` has the following parameters:
- `int lend[n]`: the amounts each lender lends
- `int payback[n]`: the payoff amounts each lender expects

#### Returns

- `int`: the maximum number of days the borrower can survive without incurring a *default*

#### Constraints

- `1 ≤ n ≤ 10^5`
- `1 ≤ lend[i] ≤ payback[i] ≤ 10^9`

