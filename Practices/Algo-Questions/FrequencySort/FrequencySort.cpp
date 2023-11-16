/*
 * @Author: Tairan Gao
 * @Date:   2023-09-08 11:42:38
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-09-08 11:50:34
 */

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

bool compare(unordered_map<int, int> &freq, int a, int b)
{
    if (freq[a] == freq[b])
        return a < b;

    return freq[a] < freq[b];
}

vector<int> frequency_sort(const vector<int> &items)
{
    unordered_map<int, int> freq;
    for (int i = 0; i < items.size(); i++)
    {
        freq[items[i]]++;
    }

    vector<int> res(items);
    sort(res.begin(), res.end(), [&freq](int a, int b)
         { return compare(freq, a, b); });
    return res;
}

int main()
{
    vector<int> items = {1, 1, 1, 2, 2, 3, 4, 5, 6, 5, 4, 3};
    vector<int> res = frequency_sort(items);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    cout << '\n';
    return 0;
}