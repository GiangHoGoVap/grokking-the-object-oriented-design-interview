#pragma once
#include <iostream>
using namespace std;

class Screen
{
public:
    bool showMessage(string message)
    {
        if (message.empty())
            return false;
        cout << message << endl;
        return true;
    }
};