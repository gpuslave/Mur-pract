#include <fstream>
// #include "hash-table.h"
#include "separate-chaining-table.h"
// #include "linear-probing-table.h"
// #include "cli-menu.h"

using namespace std;

class SymbolTable
{
private:
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

        symbol_struct(const symbol_struct &other)
        {
            symbol_name = other.symbol_name;
            type = other.type;
            attribute = other.attribute;
        }

        symbol_struct &operator=(const symbol_struct &other)
        {
            if (this != &other)
            {
                symbol_name = other.symbol_name;
                type = other.type;
                attribute = other.attribute;
            }
            return *this;
        }
    };

    HashTable<string, symbol_struct> table;

public:
    friend std::ostream &operator<<(std::ostream &os, const symbol_struct &symbol)
    {
        os << symbol.symbol_name << " " << symbol.type << " " << symbol.attribute;
        return os;
    }

    void read_file(const string &FILE_NAME)
    {
        fstream FILE_IN(FILE_NAME);

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
                // symbol_struct *temp_struct = new symbol_struct(symbol_pars[0], "function");
                table.insert(symbol_pars[0], symbol_struct(symbol_pars[0], "function"));
                break;
            }
            case 2:
            {
                if (symbol_pars[1][symbol_pars[1].size() - 1] == ')')
                {
                    table.insert(symbol_pars[1], symbol_struct(symbol_pars[1], "function", symbol_pars[0]));
                }
                else
                {
                    table.insert(symbol_pars[1], symbol_struct(symbol_pars[1], symbol_pars[0]));
                }
                break;
            }
            case 3:
            {
                table.insert(symbol_pars[2], symbol_struct(symbol_pars[2], symbol_pars[1], symbol_pars[0]));
                break;
            }
            default:
                break;
            }
        }

        FILE_IN.close();
    }

    void print_table()
    {
        table.print();
    }

    SymbolTable() : table(17) {}
};

int main()
{
    string filename = "input.txt";
    SymbolTable st;
    st.read_file(filename);
    st.print_table();
}