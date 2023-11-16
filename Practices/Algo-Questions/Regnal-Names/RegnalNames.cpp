/*
 * @Author: Tairan Gao
 * @Date:   2023-09-07 20:59:41
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-09-07 22:12:36
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <sstream>

std::vector<std::string> tokenizeBySpace(const std::string &name)
{
    std::vector<std::string> tokens;
    auto ss = std::stringstream(name);
    std::string temp;
    while (std::getline(ss, temp, ' '))
    {
        tokens.push_back(temp);
    }
    return tokens;
}

int romeToInt(const std::string &letter)
{
    std::unordered_map<std::string, int> regnalMap;
    regnalMap["I"] = 1;
    regnalMap["V"] = 5;
    regnalMap["X"] = 10;
    regnalMap["L"] = 50;
    regnalMap["C"] = 100;
    regnalMap["D"] = 500;
    regnalMap["M"] = 1000;
    regnalMap["IV"] = 4;
    regnalMap["IX"] = 9;
    regnalMap["XL"] = 40;
    regnalMap["XC"] = 90;
    regnalMap["CD"] = 400;
    regnalMap["CM"] = 900;

    int sol = 0;
    int i = 0;
    while (i < letter.size())
    {
        std::string key;
        if (i + 1 < letter.size())
        {
            key = letter.substr(i, 2);
            if (regnalMap.find(key) != regnalMap.end())
            {
                sol += regnalMap[key];
                i += 2;
                continue;
            }
        }
        key = letter.substr(i, 1);
        if (regnalMap.find(key) == regnalMap.end())
        {
            return -1;
        }
        sol += regnalMap[key];
        i += 1;
    }
    return sol;
}

bool cmp(const std::string &name1, const std::string &name2)
{
    auto tokens1 = tokenizeBySpace(name1);
    auto tokens2 = tokenizeBySpace(name2);
    if (tokens1.size() != tokens2.size())
    {
        return name1 < name2;
    }
    int len = tokens1.size();
    int i = 0;
    while (i < len - 1)
    {
        if (tokens1[i] == tokens2[i])
        {
            i++;
        }
        else
        {
            return tokens1[i] < tokens2[i];
        }
    }
    int num1 = romeToInt(tokens1[i]);
    int num2 = romeToInt(tokens2[i]);
    return num1 < num2;
}

std::vector<std::string> sortRegnalNames(const std::vector<std::string> &v)
{
    std::vector<std::string> v_sorted(v);
    std::sort(v_sorted.begin(), v_sorted.end(), cmp);
    return v_sorted;
}

int main()
{

    std::vector<std::string> input({
        "Louis IX",
        "Louis XX",
        "Louis VIII",
        "Philippe I",
        "Philip II",
    });

    auto sol = sortRegnalNames(input);
    for (auto &s : sol)
    {
        std::cout << s << std::endl;
    }

    return 0;
}