#include <iostream>
#include "hash-table.h"
// #include "separate-chaining-table.h"
#include "linear-probing-table.h"

using namespace std;

int main()
{
    LinearProbingTable<int, int> a(13);
    a.print();
}