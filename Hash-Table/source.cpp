#include <fstream>
#include "hash-table.h"
// #include "separate-chaining-table.h"
#include "linear-probing-table.h"

using namespace std;

int main()
{
    LinearProbingTable<char, int> a;

    // a.print();
    // cout << endl
    //      << a.isEmpty() << endl;

    a.insert('a', 1);
    a.print();
    a.insert('c', 2);
    a.print();
    a.insert('b', 3);
    a.print();
    a.insert('B', 4);
    a.insert('B', 4);
    a.print();
    a.insert('d', 5);
    a.print();
    a.insert('u', 6);
    a.print();
    a.insert('h', 7);
    a.insert('p', 8);
    a.insert('R', 9);
    a.print();
    a.insert('v', 10);
    a.print();
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
    cout << int(a.remove('B'));
    a.print();
    cout << int(a.remove('B'));
    a.print();
    // int *a1 = new int(3);
    // int *a2 = new int(4);
    // int *a3 = new int(5);

    // vector<int *> v1 = {a1, a2, a3, a1};
    // vector<int *> v2 = {a3, a2, a1};
    // swap(v1, v2);
    // cout << *v1[0] << " - " << *a3;
    // cout << endl
    //      << v1.size() << v2.size();
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