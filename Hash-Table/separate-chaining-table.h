#pragma once
#include "hash-table.h"

template <typename key_t, typename val_t>
class SeparateChainingTable : public HashTable<key_t, val_t>
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
                this->key = other.key;
                this->val = other.val;
            }
            return *this;
        }
    };

    std::vector<std::list<data_t>> cells;

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
        int newSize = closestPrimeTo(tableSize * 2);
        std::vector<data_t_p> newVec(newSize, nullptr);
        d_state.clear();
        d_state.resize(newSize, FREE);

        for (int i = 0; i < newVec.size(); i++)
            newVec[i] = nullptr;

        tableSize = newSize;

        // re-hash
        for (int j = 0; j < dict.size(); j++)
        {
            if (dict[j] == nullptr)
                continue;

            int i = 0;
            int q = 0;

            while (i != newSize)
            {
                q = unif_hash(dict[j]->key, i);
                if (newVec[q] == nullptr)
                {
                    newVec[q] = dict[j];
                    d_state[q] = BUSY;
                    break;
                }
                i++;
            }
        }

        std::swap(dict, newVec);
        newVec.clear();
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
            if (loadFactor >= 10)
            {
                expandTable();
                calcLoadFactor();
            }
        }
        else
            loadFactor = 0;
    }

public:
    SeparateChainingTable(int tableSize = 17)
    {
        this->tableSize = tableSize;
        cells.resize(tableSize, std::list<data_t>());
    }

    ~SeparateChainingTable()
    {
        clear();
    }

    void insert(key_t key, val_t val);
    bool remove(key_t key);
    bool find(key_t key);

    void clear()
    {
        for (auto &cell : cells)
        {
            cell.clear();
        }
        stored = 0;
    }

    int getSize()
    {
        return tableSize;
    }

    bool isEmpty()
    {
        return stored == 0;
    }

    val_t get(key_t key);

    void print()
    {
        for (int i = 0; i < tableSize; i++)
        {
            std::cout << "Bucket " << i << ": ";
            for (const auto &data : cells[i])
            {
                std::cout << "(" << data.key << ", "
                          << ") ";
            }
            std::cout << std::endl;
        }
    }

protected:
    virtual int hash(key_t key);
};