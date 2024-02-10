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
    };
    using data_t_p = data_t *;
    std::vector<data_t_p> dict;

public:
    LinearProbingTable(int tableSize)
    {
        this->tableSize = tableSize;
        dict.reserve(tableSize);

        for (int i = 0; i < tableSize; i++)
        {
            dict[i] = nullptr;
        }
    }

    ~LinearProbingTable() = default;

    void insert(key_t, val_t)
    {
        return;
    }

    bool remove(key_t)
    {
        return false;
    }

    bool find(key_t)
    {
        return false;
    }

    void clear()
    {
        return;
    }

    int getSize()
    {
        return tableSize;
    }

    bool isEmpty()
    {
        return false;
    }

    val_t get(key_t)
    {
        return 0;
    }

    void print()
    {
        for (int i = 0; i < tableSize; i++)
        {
            // std::cout << dict[i].key << "\\-/" << dict[i].val << std::endl;
            std::cout << dict[i] << std::endl;
        }
    }

protected:
    int hash(key_t)
    {
        return 1;
    }

    int unif_hash(key_t, int)
    {
        return 1;
    }
};
