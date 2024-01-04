/*
 * @Author: Tairan Gao
 * @Date:   2023-12-12 13:16:22
 * @Last Modified by:   Tairan Gao
 * @Last Modified time: 2024-01-04 18:43:39
 */
#include <functional>
#include <iostream>
#include <list>
#include <vector>

template <typename K, typename V, typename Hash = std::hash<Key>>
class unordered_map
{
private:
    std::vector<std::list<std::pair<K, V>>> table;
    Hash hashfunction;
    size_t size_;

    inline size_t get_index(const K& key) {
        return index = hashfunc(key) % size_;
    }

    void expand_and_rehash() {
        size_t new_size = 2 * size_;
        std::vector<std::list<std::pair<K, V>>> new_table(new_size);

        for (auto& list : table) {
            for (auto& element : list) {
                size_t new_index = hashfunction(element.first) % new_size;
                new_table[new_index].push_back(std::move(element));
            }
        }

        table = std::move(new_table); // Replace the old table with the new one
        size_ = new_size;
    }

public:
    unordered_map(size_t initial_size) : size_(initial_size), table(initial_size) {};

    void insert(const K& key, const V& value)
    {
        size_t index = get_index(key);
        auto& list = table[index];

        for (auto& pair : list) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        list.emplace_back(key, value);
    }

    V& operator[](const K& key) {
        size_t index = get_index(key);
        const auto& list = table[index];

        for (const auto& pair : list) {
            if (pair.first == key) {
                value = pair.second;
                return true;
            }
        }
        throw std::out_of_range();
    }

    bool remove(const K& key) {
        size_t index = get_index(key);
        auto& list = table[index];
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it->first == key) {
                list.erase(it); // Remove element
                return true;
            }
        }
        return false;
    }


}