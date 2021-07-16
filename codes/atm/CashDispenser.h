#pragma once
#include <iostream>
using namespace std;

class CashDispenser
{
private:
    int INITIAL_COUNT = 500;
    int billCount;

public:
    CashDispenser()
    {
        this->billCount = INITIAL_COUNT;
    }
    void dispenseCash(int amount)
    {
        int billsRequired = amount / 20;
        billCount -= billsRequired;
    }
    bool canDispenseCash(int amount)
    {
        int billsRequired = amount / 20;
        return (billCount >= billsRequired);
    }
};