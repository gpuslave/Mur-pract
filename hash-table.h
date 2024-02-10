#include <list>
#include <vector>
#include <algorithm>

typedef int key_t;
typedef int val_t;

class HashTable {
public:
  virtual void insert(key_t key, val_t val) = 0;
  virtual bool remove(key_t key) = 0;
  virtual bool find(key_t key) = 0;

  virtual void clear() = 0;
  virtual int getsize() = 0;
  virtual bool isempty() = 0;
  virtual val_t get(key_t key) = 0;

  virtual void print() = 0;

protected:
  virtual int hash(key_t key) = 0;
};