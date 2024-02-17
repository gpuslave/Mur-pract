#include <fstream>
#include "hash-table.h"
// #include "separate-chaining-table.h"
// #include "linear-probing-table.h"

using namespace std;

struct symbol_struct
{
    string symbol_name;
    string type;
    string attribute;

    symbol_struct(string s_n, string t = "none", string a = "none")
    {
        symbol_name = s_n;
        type = t;
        attribute = a;
    }
};

vector<symbol_struct *> read_file(const string &FILE_NAME)
{
    fstream FILE_IN(FILE_NAME);
    vector<symbol_struct *> main_vec;

    string gls = "";
    int cnt = 0;
    while (getline(FILE_IN, gls))
    {
        cnt++;
        string temp = "";
        vector<string> symbol_pars;
        for (size_t i = 0; i < gls.size(); i++)
        {
            char p = gls[i];
            if (p != ' ' && gls.size() - 1 > i)
            {
                temp += p;
            }
            else if (i == gls.size() - 1)
            {
                temp += p;
                symbol_pars.push_back(temp);
                temp.clear();
            }
            else
            {
                symbol_pars.push_back(temp);
                temp.clear();
            }
        }

        switch (symbol_pars.size())
        {
        case 1:
        {
            symbol_struct *temp_struct = new symbol_struct(symbol_pars[0], "function");
            main_vec.push_back(temp_struct);
            break;
        }
        case 2:
        {
            if (symbol_pars[1][symbol_pars.size() - 1] == ')')
            {
                symbol_struct *temp_struct = new symbol_struct(symbol_pars[1], "function", symbol_pars[0]);
                main_vec.push_back(temp_struct);
            }
            else
            {
                symbol_struct *temp_struct = new symbol_struct(symbol_pars[1], symbol_pars[0]);
                main_vec.push_back(temp_struct);
            }
            break;
        }
        case 3:
        {
            symbol_struct *temp_struct = new symbol_struct(symbol_pars[2], symbol_pars[1], symbol_pars[0]);
            main_vec.push_back(temp_struct);
            break;
        }

        default:
            break;
        }
        // for (string str : symbol_pars)
        //     cout << str;
        // cout << endl;
        // cout << symbol_pars.size() << endl;
    }

    FILE_IN.close();
    return main_vec;
}

int main()
{
    string filename = "input.txt";
    vector<symbol_struct *> vec = read_file(filename);

    for (symbol_struct *ptr : vec)
        cout << ptr->attribute << " " << ptr->type << " " << ptr->symbol_name << endl;

    // // LINEAR PROBING
    // LinearProbingTable<char, int> a;

    // // a.print();
    // // cout << endl
    // //      << a.isEmpty() << endl;

    // a.insert('a', 1);
    // a.print();
    // a.insert('c', 2);
    // a.print();
    // a.insert('b', 3);
    // a.print();
    // a.insert('B', 4);
    // a.insert('B', 4);
    // a.print();
    // a.insert('d', 5);
    // a.print();
    // a.insert('u', 6);
    // a.print();
    // a.insert('h', 7);
    // a.insert('p', 8);
    // a.insert('R', 9);
    // a.print();
    // a.insert('v', 10);
    // a.print();
    // // a.insert('a', 12);
    // // a.insert('a', 12);
    // // a.insert('a', 12);
    // // a.insert('a', 12);
    // // a.insert('A', 123);
    // // a.insert('b', 423);
    // // a.insert('B', 423);
    // // a.print();
    // // a.insert('B', 423);
    // // a.insert('B', 423);
    // // a.insert('B', 423);
    // // a.insert('B', 423);
    // // a.insert('B', 423);
    // // a.print();

    // cout << a.find('A') << "  " << a.find('b') << "  " << a.find('B') << endl;
    // cout << int(a.remove('B'));
    // a.print();
    // cout << int(a.remove('B'));
    // a.print();
    // // int *a1 = new int(3);
    // // int *a2 = new int(4);
    // // int *a3 = new int(5);

    // // vector<int *> v1 = {a1, a2, a3, a1};
    // // vector<int *> v2 = {a3, a2, a1};
    // // swap(v1, v2);
    // // cout << *v1[0] << " - " << *a3;
    // // cout << endl
    // //      << v1.size() << v2.size();
    // // cout << endl;
    // // vector<int> u;
    // // u.reserve(3);
    // // u[0] = int(3);
    // // u[1] = u[2] = 0;

    // // cout << u[0];
    // // u.resize(6, 0);
    // // cout << u[0];

    // // cout << endl
    // //      << a.isEmpty() << endl;
}