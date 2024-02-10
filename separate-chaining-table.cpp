#include "separate-chaining-table.h"

SeparateChainingTable::SeparateChainingTable(int tableSize) {
    this->tableSize = tableSize;
    cells.reserve(tableSize);
}

// SeparateChainingTable::~SeparateChainingTable();

void SeparateChainingTable::insert(key_t key, val_t val) {
    int index = hash(key);
    std::list<data_t> temp = cells[index];

    std::list<data_t>::iterator found_it =
        std::find_if(temp.begin(), temp.end(),
                     [key](data_t &data) { return data.key == key; });

    if (found_it == temp.end()) {
      data_t elem{key, val};
      temp.push_back(elem);
    } else
      found_it->val = val;
}