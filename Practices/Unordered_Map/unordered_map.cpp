/*
 * @Author: Tairan Gao
 * @Date:   2023-12-12 13:16:22
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2023-12-12 13:53:29
 */
#include <functional>
#include <iostream>
#include <list>
#include <vector>

template <typename K, typename V, class Hash = std::hash<Key>>
class unordered_map
{
private:
    std::vector<std::list<std::pair<K, V>>> table;
    Hash hashfunction;

public:
    unordered_map() = default;

    void insert(const K &key, const V &value)
    {
        size_t index = hashfunc(key) % table.capacity;
    }
}