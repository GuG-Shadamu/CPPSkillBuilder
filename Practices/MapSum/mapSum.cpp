/*
 * @Author: Tairan Gao
 * @Date:   2023-10-02 22:11:15
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-10-03 09:55:37
 */

#include <unordered_map>
#include <string>
#include <memory>
#include <deque>
#include <cassert>

struct Trie
{
    std::unordered_map<char, std::unique_ptr<Trie>> children = {};
    int value = 0;
    bool is_end = false;
};

class MapSum
{
private:
    std::unique_ptr<Trie> root;

public:
    MapSum(const std::unordered_map<std::string, int> &data);
    int sum(const std::string &prefix) const;
    void addWord(const std::string &word, int value);
};

MapSum::MapSum(const std::unordered_map<std::string, int> &data)
{
    root = std::make_unique<Trie>();

    for (const auto &pair : data)
    {
        addWord(pair.first, pair.second);
    }
}

int MapSum::sum(const std::string &prefix) const
{
    int ret = 0;
    auto node = root.get();
    for (size_t i = 0; i < prefix.length(); i++)
    {
        auto &dict = node->children;
        const char c = prefix[i];
        auto it = dict.find(c);
        if (it == dict.end())
        {
            return 0;
        }
        node = dict[c].get();
    }
    std::deque<Trie *> queue{node};
    while (!queue.empty())
    {
        auto queue_node = queue.front();
        ret += queue_node->value;
        if (!queue_node->children.empty())
        {
            for (const auto &pair : queue_node->children)
            {
                queue.push_back(pair.second.get());
            }
        }
        queue.pop_front();
    }
    return ret;
}

void MapSum::addWord(const std::string &word, int value)
{
    auto node = root.get();

    for (size_t i = 0; i < word.length(); i++)
    {
        auto &dict = node->children;
        const char c = word[i];
        auto it = dict.find(c);
        if (it == dict.end())
        {
            dict[c] = std::make_unique<Trie>();
        }
        node = dict[c].get();
    }

    node->is_end = true;
    node->value = value;
}

#include <cassert>
#include <iostream>
#include <unordered_map>

// Your MapSum class implementation goes here...

void testBasicFunctionality()
{
    std::unordered_map<std::string, int> data = {{"apple", 3}, {"app", 5}, {"banana", 2}};
    MapSum mapSum(data);

    assert(mapSum.sum("app") == 8);
    std::cout << "Test Basic Functionality passed!" << std::endl;
}

void testEmptyPrefix()
{
    std::unordered_map<std::string, int> data = {{"apple", 3}, {"banana", 2}};
    MapSum mapSum(data);

    assert(mapSum.sum("") == 5);
    std::cout << "Test Empty Prefix passed!" << std::endl;
}

void testPrefixNotPresent()
{
    std::unordered_map<std::string, int> data = {{"apple", 3}, {"banana", 2}};
    MapSum mapSum(data);

    assert(mapSum.sum("grape") == 0);
    std::cout << "Test Prefix Not Present passed!" << std::endl;
}

void testSingleEntry()
{
    std::unordered_map<std::string, int> data = {{"apple", 3}};
    MapSum mapSum(data);

    assert(mapSum.sum("a") == 3);
    std::cout << "Test Single Entry passed!" << std::endl;
}

void testMultipleMatches()
{
    std::unordered_map<std::string, int> data = {{"apple", 3}, {"app", 5}, {"apricot", 2}};
    MapSum mapSum(data);

    assert(mapSum.sum("ap") == 10);
    std::cout << "Test Multiple Matches passed!" << std::endl;
}

void testNoMatches()
{
    std::unordered_map<std::string, int> data = {{"apple", 3}, {"banana", 2}};
    MapSum mapSum(data);

    assert(mapSum.sum("z") == 0);
    std::cout << "Test No Matches passed!" << std::endl;
}

void testUpdatingValues()
{
    std::unordered_map<std::string, int> data = {{"apple", 3}};
    MapSum mapSum(data);

    assert(mapSum.sum("app") == 3);

    mapSum.addWord("apple", 5);
    assert(mapSum.sum("app") == 5);
    std::cout << "Test Updating Values passed!" << std::endl;
}

int main()
{
    testBasicFunctionality();
    testEmptyPrefix();
    testPrefixNotPresent();
    testSingleEntry();
    testMultipleMatches();
    testNoMatches();
    testUpdatingValues();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
