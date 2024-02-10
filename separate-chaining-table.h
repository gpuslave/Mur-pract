#include "hash-table.h"

class SeparateChainingTable : public HashTable {
private:
  int tableSize;

public:
  SeparateChainingTable(int tableSize);

  struct data_t {
    key_t key;
    val_t val;
  };

  std::vector<std::list<data_t>> cells;

  virtual void insert(key_t key, val_t val);
  virtual bool remove(key_t key);
  virtual bool find(key_t key);

  virtual void clear();
  virtual int getsize();
  virtual bool isempty();
  virtual val_t get(key_t key);

  virtual void print();
  ~SeparateChainingTable();

protected:
  virtual int hash(key_t key);
};