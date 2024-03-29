#pragma once

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <cctype>

// #define NIL -1
// typedef int key_t;
// typedef int val_t;

template <typename key_t, typename val_t>
class HashTable
{
public:
    virtual int insert(key_t key, val_t val) = 0;
    virtual bool remove(key_t key) = 0;
    virtual int find(key_t key) = 0;

    virtual void clear() = 0;
    virtual int getSize() = 0;
    virtual bool isEmpty() = 0;
    virtual val_t get(key_t key) = 0;

    virtual void print() = 0;

protected:
    virtual int hash(key_t key) = 0;
};