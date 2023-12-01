/*
 * @Author: Tairan Gao
 * @Date:   2023-12-01 13:53:43
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-12-01 15:41:22
 */
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <string_view>
#include <unordered_map>
#include <iostream>
#include <random>
#include <ctime>

class LZWEncoder
{
private:
    std::unordered_map<std::string_view, uint16_t> code_map = {};

public:
    void reset()
    {
        code_map = {};
    }
    std::vector<uint16_t> encode(std::string in)
    {
        std::vector<uint16_t> sol;
        std::string_view sv_in = in;
        uint16_t temp_code;
        int length;
        uint16_t last_code = 26;
        int i = 0;
        while (i < sv_in.size())
        {
            temp_code = sv_in[i] - 'A' + 1;
            length = 2;
            while (i + length <= sv_in.size())
            {
                std::string_view sub_sv = sv_in.substr(i, length);
                auto it = code_map.find(sub_sv);
                if (it == code_map.end())
                {
                    code_map[sub_sv] = ++last_code;
                    break;
                }
                else
                {
                    temp_code = it->second;
                    length++;
                }
            }

            i = i + length - 1;
            sol.push_back(temp_code);
        }
        return sol;
    }
};

class LZWDncoder
{
private:
    std::unordered_map<uint16_t, std::string> int_to_string = {};
    std::unordered_map<std::string, uint16_t> string_to_int = {};
    uint16_t last_code = 26;

public:
    void reset()
    {
        int_to_string = {};
        string_to_int = {};
        last_code = 26;
    }
    std::string decode(std::vector<uint16_t> in)
    {
        std::string output;
        int start = 0;
        int count = 0;
        for (int i = 0; i < in.size(); i++)
        {
            auto ele = in[i];
            if (ele <= 26)
            {
                output += char('A' + ele - 1);
                count++;
            }
            else
            {
                output += int_to_string[ele];
            }
            if (i == in.size() - 1)
                break;
            int length = 2;
            while (start + length - 1 < output.size())
            {
                auto sub = output.substr(start, length);
                auto it = string_to_int.find(sub);
                if (it == string_to_int.end())
                {
                    string_to_int[sub] = ++last_code;
                    int_to_string[last_code] = sub;
                    start++;
                }
                else
                {
                    length++;
                }
            }
        }
        return output;
    }
};

std::string generateRandomString(size_t length)
{
    // Characters to choose from
    std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Random number generator using a Mersenne Twister
    std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr))); // seed with current time
    std::uniform_int_distribution<> distribution(0, chars.size() - 1);

    std::string randomString;
    for (size_t i = 0; i < length; ++i)
    {
        // Generate a random index and append the character to the string
        randomString += chars[distribution(generator)];
    }

    return randomString;
}

int main()
{
    LZWEncoder encoder{};
    LZWDncoder decoder{};
    for (int i = 5; i < 15; i++)
    {
        encoder.reset();
        decoder.reset();
        auto ss = generateRandomString(i);
        auto code = encoder.encode(ss);
        auto check = decoder.decode(code);
        if (check != ss)
        {
            std::cout << ss << " vs " << check << "\n";
        }
    }
    return 0;
}