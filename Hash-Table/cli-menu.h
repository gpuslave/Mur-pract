#pragma once

#include <iostream>
#include <string>

template <typename dict>
class Menu
{
private:
    using key_t = char;
    using val_t = int;

    dict dictionary;
    bool isInit;
    bool isEnded;

    key_t getKeyInput()
    {
        key_t temp;
        std::cout << "Please enter key: ";
        while (!(std::cin >> temp))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        return temp;
    }

    val_t getValueInput()
    {
        val_t temp;
        std::cout << "Please enter value: ";
        while (!(std::cin >> temp))
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
        return temp;
    }

    void init()
    {
        // some initialization
        isInit = true;
    }

public:
    Menu() : isInit(false), isEnded(false) {}
    ~Menu() {}

    void start()
    {
        while (!isEnded)
        {
            display_options();
            getInput();
        }
    }

    void display_options()
    {
        int i = 1;
        std::cout << std::endl;

        std::cout << std::setw(2) << i++ << "."
                  << "  Init table" << std::endl;
        std::cout << std::setw(2) << i++ << "."
                  << "  Insert key-value" << std::endl;
        std::cout << std::setw(2) << i++ << "."
                  << "  Delete key" << std::endl;
        std::cout << std::setw(2) << i++ << "."
                  << "  Find key" << std::endl;
        std::cout << std::setw(2) << i++ << "."
                  << "  Print table" << std::endl;
        std::cout << std::setw(2) << i++ << "."
                  << "  Clear table" << std::endl;
        std::cout << std::setw(2) << i++ << "."
                  << "  Exit cli" << std::endl;

        std::cout << std::endl;
    }

    int getInput()
    {
        int input;
        while (!(std::cin >> input) || input > 7 || input < 1)
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }

        switch (input)
        {
        case 1:
            if (isInit)
                std::cout << "Table is already initialized.";
            else
                init();
            break;
        case 2:
        {
            if (isInit)
            {
                key_t key = getKeyInput();
                val_t val = getValueInput();

                if (dictionary.find(key) >= 0)
                {
                    std::cout << "Insertion fail, key already exists" << std::endl;
                }
                else
                {
                    dictionary.insert(key, val);
                }
            }
            else
                std::cout << "Table is not yet initialized" << std::endl;
            break;
        }
        case 3:
        {
            if (isInit)
            {
                key_t del_key = getKeyInput();
                if (dictionary.find(del_key) == -1)
                    std::cout << "Deletion fail, no such key" << std::endl;
                else
                {
                    dictionary.remove(del_key);
                }
            }
            else
                std::cout << "Table is not yet initialized" << std::endl;

            break;
        }
        case 4:
        {
            if (isInit)
            {
                key_t key = getKeyInput();
                val_t found_val = dictionary.get(key);
                if (found_val == -1)
                    std::cout << "Find fail, no such key" << std::endl;
                std::cout << found_val << std::endl;
            }
            else
                std::cout << "Table is not yet initialized" << std::endl;
            break;
        }
        case 5:
            if (isInit)
                dictionary.print();
            else
                std::cout << "Table is not yet initialized" << std::endl;
            break;
        case 6:
            if (isInit)
                dictionary.clear();
            else
                std::cout << "Table is not yet initialized" << std::endl;

            break;
        case 7:
            isEnded = true;
            break;

        default:
            break;
        }

        return 1;
    }
};