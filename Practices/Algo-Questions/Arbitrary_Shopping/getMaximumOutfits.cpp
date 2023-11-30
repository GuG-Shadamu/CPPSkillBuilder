/*
 * @Author: Tairan Gao
 * @Date:   2023-11-30 15:10:38
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-11-30 16:15:04
 */
#include <vector>
#include <algorithm>

int getMaxOutfits(int n, const std::vector<int> &outfits, int money)
{
    int res = 0;
    int cur_num = 0;
    int cur_sum = 0;
    int start = 0;

    for (int i = 0; i < n; ++i)
    {
        cur_sum += outfits[i];
        cur_num++;

        while (cur_sum > money)
        {
            cur_sum -= outfits[start];
            cur_num--;
            start++;
            if (start > i)
            {
                return res;
            }
        }

        res = std::max(cur_num, res);
    }

    return res;
}