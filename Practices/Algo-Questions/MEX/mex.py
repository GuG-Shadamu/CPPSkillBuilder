# Python3 program for the above approach

# Function to return maximum MEX of
# all K length subarray


def maxMEX(arr, N, x):
    # Stores element from 1 to N + 1
    # is nor present in subarray
    new_arr = [0] * N

    for i in range(len(arr)):
        r = arr[i] % x

        new_arr[i] = r

    visited = set()

    for i in range(len(new_arr)):
        element = new_arr[i]
        while element in visited:
            element += x

        visited.add(element)
        new_arr[i] = element

    print(new_arr)
    res = min(set(range(len(new_arr) + 2)) - set(new_arr))
    print(res)


# Driver code
if __name__ == "__main__":
    # Given array
    arr = [0, 1, 2, 1, 3]

    # Size of the array
    N = len(arr)

    # Given length of subarray
    K = 3

    # Function Call
    maxMEX(arr, N, K)

# This code is contributed by Shivam Singh
