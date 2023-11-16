/*
 * @Author: Tairan Gao
 * @Date:   2023-08-28 16:57:06
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-08-28 17:14:15
 */

#include <iostream>
#include <limits.h>
#include <string>

using namespace std;

string k_smallest_substring(string s, int k)
{
    int left = 0;
    int right = 0;

    int ones;
    int cur_min = INT_MAX;
    string cur_sol = "";

    if (s[0] == '1')
        ones = 1;
    else
        ones = 0;

    while (right < s.size() and left <= right)
    {
        if (ones == k)
        {
            string temp_str = s.substr(left, right - left + 1);
            int temp_val = stoi(temp_str, 0, 2);
            if (temp_val <= cur_min)
            {
                cur_min = temp_val;
                cur_sol = temp_str;
            }
            if (s[left] == '1')
            {
                ones -= 1;
            }
            left += 1;
            continue;
        }
        if (ones > k)
        {
            if (s[left] == '1')
            {
                ones -= 1;
            }
            left += 1;
            continue;
        }
        if (ones < k)
        {
            right += 1;
            if (s[right] == '1')
            {
                ones += 1;
            }
            continue;
        }
    }
    return cur_sol;
}

// help me generate a number of test cases for the above function
int main()
{
    string s = "1001010001";
    int k = 3;
    cout << k_smallest_substring(s, k) << endl;

    return 0;
}