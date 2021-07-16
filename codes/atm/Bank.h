#pragma once
#include <iostream>
#include <vector>
#include "Account.h"
using namespace std;

class Bank
{
private:
    vector<Account *> accounts;
    Account *GetAccount(int accountNumber)
    {
        for (int i = 0; i < accounts.size(); i++)
        {
            if (accounts[i]->getAccountNumber() == accountNumber)
            {
                return accounts[i];
            }
        }
        return NULL;
    }

public:
    bool AuthenticateUser(int accountNumber, int pin)
    {
        Account *userAccount = GetAccount(accountNumber);
        if (userAccount != NULL)
        {
            return userAccount->validatePIN(pin);
        }
        else
            return false;
    }
    double GetAvailableBalance(int userAccountNumber)
    {
        Account *userAccount = GetAccount(userAccountNumber);
        return userAccount->getAvailableBalance();
    }
    double GetTotalBalance(int userAccountNumber)
    {
        Account *userAccount = GetAccount(userAccountNumber);
        return userAccount->getTotalBalance();
    }
    void Credit(int userAccountNumber, double amount)
    {
        Account *userAccount = GetAccount(userAccountNumber);
        userAccount->credit(amount);
    }
    void Debit(int userAccountNumber, double amount)
    {
        Account *userAccount = GetAccount(userAccountNumber);
        userAccount->debit(amount);
    }
    void addCustomer(Account *newCus)
    {
        this->accounts.push_back(newCus);
    }
};