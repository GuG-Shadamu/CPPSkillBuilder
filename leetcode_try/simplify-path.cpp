/*
 * @Author: Tairan Gao
 * @Date:   2023-06-07 11:32:39
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-06-07 12:02:48
 */

#include <vector>
#include <iostream>
#include <string>
#include <deque>
using namespace std;

class Solution
{
public:
    string simplifyPath(string path)
    {
        string sol = "";
        deque<string> path_deque;
        string temp = "";
        for (size_t i = 0u; i < path.size(); i++)
        {

            if (path[i] != '/')
            {
                temp += path[i];
            }
            else
            {
                if (temp == "")
                    continue;
                else if (temp == ".")
                    temp = "";
                else if (temp == "..")
                {
                    if (!path_deque.empty())
                    {
                        path_deque.pop_front();
                    }
                    temp = "";
                }
                else
                {
                    path_deque.push_front(temp);
                    temp = "";
                }
            }
        }

        while (!path_deque.empty())
        {
            sol += "/";
            sol += path_deque.back();
            path_deque.pop_back();
        }
        if (sol == "")
        {
            sol += "/";
        }
        return sol;
    }
};

int main()
{
    Solution s;
    cout << s.simplifyPath("/home/") << endl;
    cout << s.simplifyPath("/../") << endl;
    cout << s.simplifyPath("/home//foo/") << endl;
    cout << s.simplifyPath("/a/./b/../../c/") << endl;
    cout << s.simplifyPath("/a/../../b/../c//.//") << endl;
    cout << s.simplifyPath("/a//b////c/d//././/..") << endl;

    return 0;
}