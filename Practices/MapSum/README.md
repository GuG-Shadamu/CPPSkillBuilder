# MapSum Trie Implementation in C++

## Overview
This project features a custom implementation of a `MapSum` class in C++, which uses a Trie data structure to efficiently store and query key-value pairs. The primary functionality is to calculate the sum of all values that have a common prefix.

## Features
- **Trie Data Structure:** Efficiently stores strings and their corresponding integer values.
- **Prefix Sum Calculation:** Allows calculation of the sum of all values that share a specific prefix.
- **Dynamic Insertion:** Supports adding new key-value pairs to the Trie.
- **Efficient Queries:** Provides fast lookups for prefix sums.

## Implementation
- `MapSum` class initializes with a set of key-value pairs and provides functionality to add more pairs.
- `sum` function calculates the cumulative value of all strings in the Trie that start with a given prefix.
- Trie nodes are implemented with an `unordered_map` for children, allowing for efficient character-to-node mapping.

## Testing
The implementation includes various test cases to validate the functionality:
- Basic Functionality: Checks the sum calculation for a common prefix.
- Empty Prefix: Verifies the behavior when the prefix is empty.
- Prefix Not Present: Ensures correct handling when the prefix is not found.
- Single Entry: Tests the sum calculation for a Trie with a single entry.
- Multiple Matches: Validates the sum for multiple strings matching a prefix.
- No Matches: Confirms zero-sum for prefixes with no matches.
- Updating Values: Tests the Trie's ability to update values of existing keys.
