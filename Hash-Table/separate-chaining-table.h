#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <cmath>

int my_hash(const std::string &symbolName)
{
    const int x = 2;
    std::string s = symbolName + "njkvyurewqoihbjivdc";
    int result = 0;
    for (int i = s.length() - 1; i >= 0; --i)
    {
        result = (result * x + s[i]) % INT_MAX;
    }

    return result;
}

template <typename Key, typename Value>
class HashTable
{
public:
    HashTable(size_t size) : table(size) {}
    ~HashTable()
    {
        clear();
    }

    void insert(const Key &key, const Value &value)
    {
        size_t idx = hash(key);
        table[idx].push_back(std::make_pair(key, value));

        if (1.0 * size() / table.size() >= 0.8)
        {
            rehash(closestPrimeTo(table.size() * 2));
        }
    }

    Value &find(const Key &key)
    {
        size_t idx = hash(key);
        auto it = std::find_if(table[idx].begin(), table[idx].end(),
                               [&key](const auto &pair)
                               { return pair.first == key; });

        if (it != table[idx].end())
        {
            return it->second;
        }

        throw std::runtime_error("Key not found");
    }

    size_t size() const
    {
        return std::accumulate(table.begin(), table.end(), 0,
                               [](size_t total, const auto &list)
                               { return total + list.size(); });
    }

    bool empty() const
    {
        return size() == 0;
    }

    void clear()
    {
        for (auto &list : table)
        {
            list.clear();
        }
    }

    void del(const Key &key)
    {
        size_t idx = hash(key);
        auto it = std::find_if(table[idx].begin(), table[idx].end(),
                               [&key](const auto &pair)
                               { return pair.first == key; });

        if (it != table[idx].end())
        {
            table[idx].erase(it);
        }
    }

    void print()
    {
        int i = 1;
        for (const auto &list : table)
        {
            std::cout << "Bucket " << i++ << ": ";
            for (const auto &pair : list)
            {
                std::cout << "(" << pair.first << ",  "
                          << pair.second << ")  --->  ";
            }
            std::cout << std::endl;
        }

        std::cout << "load: " << 1.0 * size() / table.size() << std::endl;
    }

private:
    std::vector<std::list<std::pair<Key, Value>>> table;

    size_t hash(const Key &key) const
    {
        return my_hash(key) % table.size();
        // return std::hash<Key>{}(key) % table.size();
    }

    void rehash(size_t newSize)
    {
        std::vector<std::list<std::pair<Key, Value>>> newTable(newSize);

        for (const auto &list : table)
        {
            for (const auto &pair : list)
            {
                size_t idx = hash(pair.first) % newTable.size();
                newTable[idx].push_back(pair);
            }
        }

        table = std::move(newTable);
    }

    bool isPrime(const int &num)
    {
        if (num <= 1)
            return false;
        if (num == 2 || num == 3)
            return true;

        int sqrtNum = std::sqrt(num);
        for (int i = 2; i <= sqrtNum; i++)
        {
            if (num % i == 0)
                return false;
        }
        return true;
    }

    int closestPrimeTo(int num)
    {
        bool found = false;
        while (!found)
        {
            num++;
            found = isPrime(num);
        }
        return num;
    }
};

// #pragma once
// #include "hash-table.h"

// template <typename key_t, typename val_t>
// class SeparateChainingTable : public HashTable<key_t, val_t>
// {
// private:
//     int tableSize;
//     int stored;
//     double loadFactor;

//     struct data_t
//     {
//         key_t key;
//         val_t val;

//         data_t(key_t key_, val_t val_) : key(key_), val(val_) {}

//         data_t &operator=(const data_t &other)
//         {
//             if (this != &other)
//             {
//                 this->key = other.key;
//                 this->val = other.val;
//             }
//             return *this;
//         }
//     };

//     std::vector<std::list<data_t>> cells;

//     bool isPrime(const int &num)
//     {
//         if (num <= 1)
//             return false;
//         if (num == 2 || num == 3)
//             return true;

//         int sqrtNum = std::sqrt(num);
//         for (int i = 2; i <= sqrtNum; i++)
//         {
//             if (num % i == 0)
//                 return false;
//         }
//         return true;
//     }

//     int closestPrimeTo(int num)
//     {
//         bool found = false;
//         while (!found)
//         {
//             num++;
//             found = isPrime(num);
//         }
//         return num;
//     }

//     void expandTable()
//     {
//         int newSize = closestPrimeTo(tableSize * 2);

//         // std::vector<data_t_p> newVec(newSize, nullptr);
//         // d_state.clear();
//         // d_state.resize(newSize, FREE);

//         // for (int i = 0; i < newVec.size(); i++)
//         //     newVec[i] = nullptr;

//         // tableSize = newSize;

//         // // re-hash
//         // for (int j = 0; j < dict.size(); j++)
//         // {
//         //     if (dict[j] == nullptr)
//         //         continue;

//         //     int i = 0;
//         //     int q = 0;

//         //     while (i != newSize)
//         //     {
//         //         q = unif_hash(dict[j]->key, i);
//         //         if (newVec[q] == nullptr)
//         //         {
//         //             newVec[q] = dict[j];
//         //             d_state[q] = BUSY;
//         //             break;
//         //         }
//         //         i++;
//         //     }
//         // }

//         // std::swap(dict, newVec);
//         // newVec.clear();
//     }

//     void calcLoadFactor()
//     {
//         loadFactor = double(stored) / tableSize;
//     }

//     void updateLoadFactor()
//     {
//         if (stored > 0)
//         {
//             calcLoadFactor();
//             if (loadFactor >= 10)
//             {
//                 expandTable();
//                 calcLoadFactor();
//             }
//         }
//         else
//             loadFactor = 0;
//     }

// public:
//     SeparateChainingTable(int tableSize = 17)
//     {
//         this->tableSize = tableSize;
//         cells.resize(tableSize, std::list<data_t>());
//     }

//     ~SeparateChainingTable()
//     {
//         clear();
//     }

//     void insert(key_t key, val_t val);
//     bool remove(key_t key);
//     bool find(key_t key);

//     void clear()
//     {
//         for (auto &cell : cells)
//         {
//             cell.clear();
//         }
//         stored = 0;
//     }

//     int getSize()
//     {
//         return tableSize;
//     }

//     bool isEmpty()
//     {
//         return stored == 0;
//     }

//     val_t get(key_t key);

//     void print()
//     {
//         for (int i = 0; i < tableSize; i++)
//         {
//             std::cout << "Bucket " << i << ": ";
//             for (const auto &data : cells[i])
//             {
//                 std::cout << "(" << data.key << ", "
//                           << ") ";
//             }
//             std::cout << std::endl;
//         }
//     }

// protected:
//     int hash()
//     {
//         return data_t.key.hash % tableSize;
//     }
// };