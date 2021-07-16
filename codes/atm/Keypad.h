#pragma once
#include <iostream>
using namespace std;

class Keypad
{
public:
    string getInput()
    {
        string input;
        getline(cin, input);
        return input;
    }
};