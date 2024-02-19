#pragma once
#include "hash-table.h"

template <typename key_t, typename val_t>
class LinearProbingTable : public HashTable<key_t, val_t>
{
private:
    enum State
    {
        FREE = 1,
        BUSY = 2,
        DELETED = 3
    };

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
    std::vector<State> d_state;

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

        // в строчке 70 это уже есть, но я ей не верю.
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
            // можно сделать for но мне так удобнее
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
        // можно даже не делать if/else но так как-то читабельнее
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
        else
            loadFactor = 0;
    }

public:
    LinearProbingTable(int tableSize = 17)
    {
        this->tableSize = tableSize;
        dict.resize(tableSize, nullptr);
        d_state.resize(tableSize, FREE);
        stored = 0;
        loadFactor = 0;
    }

    ~LinearProbingTable()
    {
        clear();
        dict.clear();
        d_state.clear();
    }

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
                d_state[q] = BUSY;
                updateLoadFactor();
                return q;
            }
            else if (dict[q]->key == key)
            {
                break;
            }
            i++;
        }
        return -1;
        std::cout << "hash table overflow!" << std::endl;
    }

    int find(key_t key)
    {
        int i = 0;
        while (i != tableSize)
        {
            int q = unif_hash(key, i);
            if (dict[q] == nullptr && d_state[q] != DELETED)
                return -1;
            if (dict[q] && dict[q]->key == key)
                return q;
            i++;
        }
        return -1;
    }

    bool remove(key_t key)
    {
        int q = find(key);
        if (q >= 0)
        {
            delete dict[q];
            dict[q] = nullptr;
            d_state[q] = DELETED;
            stored--;
            updateLoadFactor();
            return true;
        }
        else
            return false;
    }

    void clear()
    {
        for (size_t i = 0; i < dict.size(); i++)
        {
            if (dict[i] != nullptr)
            {
                delete dict[i];
                dict[i] = nullptr;
            }
            d_state[i] = FREE;
        }
        stored = 0;
        updateLoadFactor();
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
        for (int i = 0; i < dict.size(); i++)
        {
            if (dict[i] != nullptr)
            {
                return false;
            }
        }
        return true;
    }

    val_t get(key_t key)
    {
        int q = find(key);
        if (q >= 0)
        {
            return dict[q]->val;
        }
        else
            return NULL; // тут надо выбрасывать исключение но мне лень это писать
    }

    void print()
    {
        std::cout << std::endl;
        for (int i = 0; i < tableSize; i++)
        {
            if (dict[i])
                std::cout << std::setw(2) << i << " " << std::setw(4) << hash(dict[i]->key) << std::setw(3) << dict[i]->key << " --- " << std::setw(2) << dict[i]->val << std::setw(4) << int(d_state[i]) << std::endl;
            else if (d_state[i] == DELETED)
            {
                std::cout << std::setw(2) << i << " "
                          << "DELETED" << std::endl;
            }
            else
                std::cout << std::setw(2) << i << " "
                          << "FREE" << std::endl;
        }
        std::cout << "debug: " << stored << "-" << dict.size() << " " << tableSize << "-" << dict.capacity() << " " << loadFactor << std::endl;
        for (auto elem : d_state)
            std::cout << elem << " ";
        std::cout << d_state.size();
        std::cout << std::endl
                  << "------------------------" << std::endl;
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

    int inverse_unif_hash(key_t key, int u_hash)
    {
        return (u_hash - hash(key)) % tableSize;
    }
};
