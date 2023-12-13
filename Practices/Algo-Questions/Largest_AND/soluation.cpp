/*
 * @Author: Tairan Gao
 * @Date:   2023-12-12 12:28:30
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-12-12 12:28:38
 */
#include <bits/stdc++.h>
using namespace std;

// Function to find the largest possible
// subset having Bitwise AND positive
void largestSubset(int a[], int N)
{
    // Stores the number of set bits
    // at each bit position
    int bit[32] = {0};

    // Traverse the given array arr[]
    for (int i = 0; i < N; i++)
    {

        // Current bit position
        int x = 31;

        // Loop till array element
        // becomes zero
        while (a[i] > 0)
        {

            // If the last bit is set
            if (a[i] & 1 == 1)
            {

                // Increment frequency
                bit[x]++;
            }

            // Divide array element by 2
            a[i] = a[i] >> 1;

            // Decrease the bit position
            x--;
        }
    }

    // Size of the largest possible subset
    cout << *max_element(bit, bit + 32);
}

// Driver Code
int main()
{
    int arr[] = {7, 13, 8, 2, 3};
    int N = sizeof(arr) / sizeof(arr[0]);
    largestSubset(arr, N);

    return 0;
}