#pragma once
#include "hash-table.h"

template <typename key_t, typename val_t>
class LinearProbingTable : public HashTable<key_t, val_t>
{
private:
    int tableSize;
    int stored;
    double loadFactor;

    struct data_t
    {
        key_t key;
        val_t val;

        data_t(key_t key_, val_t val_) : key(key_), val(val_) {}

        data_t &operator=(const data_t &other)
        {
            if (this != &other)
            {
                key = other.key;
                val = other.val;
                return *this;
            }
        }
    };
    using data_t_p = data_t *;
    std::vector<data_t_p> dict;

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

    void expandTable()
    {
        int newSize = closestPrimeTo(tableSize);
        dict.resize(newSize, nullptr);
        tableSize = newSize;
        // vector<data_t_p> newDict(newSize, nullptr);
        // for (int i = 0; i < tableSize; i++)
        // {
        //     newDict = dict[i];
        //     dict[i] = nullptr;
        // }

        // while (tableSize <= newSize)
        // {
        //     data_t_p temp = nullptr;
        //     dict.push_back(temp);
        //     tableSize++;
        // }

        // if (tableSize == newSize)
        //     std::cout << "win";

        // dict.resize(newSize);
    }

    void calcLoadFactor()
    {
        loadFactor = double(stored) / tableSize;
    }

    void updateLoadFactor()
    {
        if (stored > 0)
        {
            calcLoadFactor();
            assert(loadFactor <= 1);
            if (loadFactor >= 0.75)
            {
                expandTable();
                calcLoadFactor();
            }
        }
    }

public:
    LinearProbingTable(int tableSize)
    {
        this->tableSize = tableSize;
        dict.resize(tableSize, nullptr);

        // for (int i = 0; i < tableSize; i++)
        // {
        //     dict[i] = new data_t(i + int('a'), rand() % 20);
        // }

        // for (data_t_p elem : dict)
        //     elem = nullptr;

        for (int i = 0; i < tableSize; i++)
        {
            dict[i] = nullptr;
        }
    }

    ~LinearProbingTable() = default;

    // void testPriming()
    // {
    //     for (size_t i = 0; i < 20; i++)
    //     {
    //         std::cout << i << "  " << isPrime(i) << "  closest prime: " << closestPrimeTo(i) << std::endl;
    //     }
    // }

    int insert(key_t key, val_t val)
    {
        int i = 0;
        int q = 0;
        while (i != tableSize)
        {
            q = unif_hash(key, i);
            if (dict[q] == nullptr)
            {
                dict[q] = new data_t(key, val);
                stored++;
                updateLoadFactor();
                return q;
            }
            i++;
        }
        return -1;
        std::cout << "hash table overflow!" << std::endl;
    }

    int find(key_t key)
    {
        int i = 0;
        int q = unif_hash(key, i);
        while (dict[q] != nullptr && i != tableSize)
        {
            q = unif_hash(key, i);
            if (dict[q]->key == key)
                return q;
            i++;
        }
        return -1;
    }

    bool remove(key_t)
    {
        return false;
    }

    void clear()
    {
        for (size_t i = 0; i < dict.capacity(); i++)
        {
            if (dict[i] != nullptr)
            {
                delete dict[i];
                dict[i] = nullptr;
            }
        }
    }

    int getSize()
    {
        return tableSize;
    }

    int getLoadFactor()
    {
        return loadFactor;
    }

    bool isEmpty()
    {
        for (int i = 0; i < dict.capacity(); i++)
        {
            if (dict[i] != nullptr)
            {
                return false;
            }
        }
        return true;
    }

    val_t get(key_t)
    {
        return 0;
    }

    void print()
    {
        std::cout << std::endl;
        for (int i = 0; i < tableSize; i++)
        {
            if (dict[i])
                std::cout << std::setw(2) << i << " " << std::setw(4) << hash(dict[i]->key) << std::setw(3) << dict[i]->key << " --- " << std::setw(2) << dict[i]->val << std::endl;
            else
                std::cout << std::setw(2) << i << " "
                          << "FREE" << std::endl;
        }
        std::cout << "debug: " << stored << "-" << dict.size() << " " << tableSize << "-" << dict.capacity() << " " << loadFactor << std::endl;
        std::cout << "------------------------" << std::endl;
    }

protected:
    int hash(key_t key)
    {
        return 11 * (std::tolower(key) - 'a' + 1) % tableSize;
    }

    int unif_hash(key_t key, int i)
    {
        return (hash(key) + i) % tableSize;
    }
};
