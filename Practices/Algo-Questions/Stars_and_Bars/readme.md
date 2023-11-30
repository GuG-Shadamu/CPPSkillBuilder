# 1. Stars and Bars

Given a string `s` consisting of stars `"*"` and bars `"|"`, an array of starting indices `startIndex`, and an array of ending indices `endIndex`, determine the number of stars between any two bars within the substring between the two indices, inclusive. Note that in this problem, indexing starts at 1.

- A star is represented as an asterisk (`"*"` = ascii decimal 42)
- A bar is represented as a pipe (`"|"` = ascii decimal 124).

## Example

`s = "|**|*|**|"`

`startIndex = [1, 1]`

`endIndex = [5, 6]`

For the first pair of indices, `(1, 5)`, the substring is `|**|*`. There are 2 stars between a pair of bars.
For the second pair of indices, `(1, 6)`, the substring is `|**|*|` and there are `2 + 1 = 3` stars between bars.
Both of the answers are returned in an array, `[2, 3]`.

## Function Description

Complete the `starsAndBars` function in the editor below.

`starsAndBars` has three parameters:

- `string s`: a string to evaluate
- `int startIndex[n]`: the starting indices
- `int endIndex[n]`: the ending indices

### Constraints

- `1 ≤ n ≤ 10^5`
- `1 ≤ startIndex[i] ≤ endIndex[i] ≤ n`
- Each character of `s` is either `"*"` or `"|"`

### Input Format For Custom Testing

> Sample Case 0

#### Sample Input For Custom Testing

| STDIN    | Function                     |
| -------- | ---------------------------- |
| `*\|*\|` | `s = "*\|*\|"`               |
| `1`      | `startIndex[1]` size `n = 1` |
| `1`      | `startIndex = 1`             |
| `1`      | `endIndex[1]` size `n = 1`   |
| `3`      | `endIndex = 3`               |


#### Sample Output

```
0
```
