#pragma once
#include <iostream>
#include "Screen.h"
#include "Bank.h"
using namespace std;

class Transaction
{
private:
    int accountNumber;
    Screen userScreen;
    Bank database;

public:
    Transaction(int userAccountNumber, Screen theScreen, Bank theDatabase)
    {
        this->accountNumber = userAccountNumber;
        this->userScreen = theScreen;
        this->database = theDatabase;
    }
    int AccountNumber()
    {
        return this->accountNumber;
    }
    Screen UserScreen()
    {
        return this->userScreen;
    }
    Bank Database()
    {
        return this->database;
    }
    virtual void execute() = 0;
};