#include <fstream>
#include "hash-table.h"
// #include "separate-chaining-table.h"
#include "linear-probing-table.h"

using namespace std;

int main()
{
    const int SIZE = 6;
    LinearProbingTable<char, int> a(SIZE);
    // a.print();
    // cout << endl
    //      << a.isEmpty() << endl;

    a.insert('a', 11);
    a.insert('b', 22);
    a.print();
    a.insert('b', 22);
    a.print();
    a.insert('a', 11);
    a.print();
    a.insert('a', 11);
    a.print();
    // a.insert('a', 12);
    // a.insert('a', 12);
    // a.insert('a', 12);
    // a.print();
    // a.insert('a', 12);
    // a.insert('a', 12);
    // a.insert('a', 12);
    // a.insert('a', 12);
    // a.insert('A', 123);
    // a.insert('b', 423);
    // a.insert('B', 423);
    // a.print();
    // a.insert('B', 423);
    // a.insert('B', 423);
    // a.insert('B', 423);
    // a.insert('B', 423);
    // a.insert('B', 423);
    // a.print();

    cout << a.find('A') << "  " << a.find('b') << "  " << a.find('B') << endl;

    // cout << endl;
    // vector<int> u;
    // u.reserve(3);
    // u[0] = int(3);
    // u[1] = u[2] = 0;

    // cout << u[0];
    // u.resize(6, 0);
    // cout << u[0];

    // cout << endl
    //      << a.isEmpty() << endl;
}