/*
 * @Author: Tairan Gao
 * @Date:   2023-09-05 12:33:22
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-09-05 14:43:13
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <ctime>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <cmath>

std::vector<std::string> split(const std::string &s, char delimiter)
{
    // Check if the stream is in a good state

    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);

    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

struct Date
{
    int year;
    int month;
    int day;

    Date(std::string date)
    {
        auto tokens = split(date, '/');
        year = std::stoi(tokens[2]);
        month = std::stoi(tokens[0]);
        day = std::stoi(tokens[1]);
    }

    Date() : year(1900), month(1), day(1){};

    int operator-(const Date &other) const
    {
        struct std::tm a = {0, 0, 0, day, month, year - 1900};
        struct std::tm b = {0, 0, 0, other.day, other.month, other.year - 1900};
        std::time_t x = std::mktime(&a);
        std::time_t y = std::mktime(&b);
        return static_cast<int>(std::difftime(x, y) / (60 * 60 * 24));
    }

    bool operator<(const Date &other) const
    {
        return (*this - other < 0);
    }
};

int main()
{
    std::vector<std::string> inputs2 = {
        "CSCO,10/18/2024,41.89",
        "AMZN,10/10/2024,113.67",
        "AMZN,10/18/2024,120.5",
        "CSCO,10/10/2024,43.12"};

    std::vector<std::string> inputs1 = {
        "IBM,12/01/2023,132.05",
        "IBM,12/03/2023,135.19",
        "IBM,12/18/2023,134.07",
        "AAPL,12/01/2023,187.19",
        "AAPL,12/04/2023,164.33",
        "AAPL,12/20/2023,180.94",
        "AAPL,12/21/2023,179.65",
        "GOOG,12/01/2023,116.41",
        "GOOG,12/07/2023,111.36",
        "GOOG,12/19/2023,112.19"};

    std::unordered_map<int, std::vector<double>> date_to_stock;
    std::unordered_map<std::string, int> stock_to_idx;
    std::unordered_set<std::string> stock_names;
    std::set<int> dates_set;
    std::vector<int> dates;
    int idx = 0;
    for (const auto &input : inputs1)
    {
        auto tokens = split(input, ',');
        std::string stock_name = tokens[0];
        int date = Date(tokens[1]) - Date();
        dates_set.insert(date);
        stock_names.insert(stock_name);
    }

    for (const auto &input : inputs1)
    {
        auto tokens = split(input, ',');
        std::string stock_name = tokens[0];
        int date = Date(tokens[1]) - Date();
        double price = std::stod(tokens[2]);
        if (stock_to_idx.find(stock_name) == stock_to_idx.end())
        {
            stock_to_idx[stock_name] = idx;
            idx++;
        }

        auto it1 = date_to_stock.find(date);
        if (it1 == date_to_stock.end())
        {
            date_to_stock[date] = std::vector<double>(stock_names.size());
        }

        date_to_stock[date][stock_to_idx[stock_name]] = price;
    }
    for (auto &it : dates_set)
    {
        dates.push_back(it);
    }

    std::vector<std::vector<double>> dp(dates.size() + 1, std::vector<double>(idx + 1, 0.0));
    dp[0][0] = 1000.0;

    for (int i = 1; i < dates.size() + 1; i++)
    {
        int cur_date = dates[i - 1];
        dp[i] = dp[i - 1];
        if (date_to_stock[cur_date].empty())
        {
            continue;
        }

        for (int j = 0; j < date_to_stock[cur_date].size(); j++)
        {
            if (dp[i - 1][j + 1] != 0 && date_to_stock[cur_date][j] != 0)
            {
                dp[i][0] = std::max(dp[i][0], dp[i - 1][j + 1] * date_to_stock[cur_date][j]);
            }
        }

        for (int j = 0; j < date_to_stock[cur_date].size(); j++)
        {
            if (date_to_stock[cur_date][j] != 0)
            {
                dp[i][j + 1] = dp[i][0] / date_to_stock[cur_date][j];
            }
        }
    }
    int res = dp[dates_set.size()][0] - 1000.0;

    std::cout << std::round(res) << std::endl;

    return 0;
}