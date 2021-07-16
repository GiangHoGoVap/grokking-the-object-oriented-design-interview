#include <iostream>
using namespace std;

class Account
{
private:
    int accountNumber;
    int PIN;
    double totalBalance;
    double availableBalance;

public:
    Account(int theAccountNumber, int thePIN, double theAvailableBalance, double theTotalBalance)
    {
        this->accountNumber = theAccountNumber;
        this->PIN = thePIN;
        this->availableBalance = theAvailableBalance;
        this->totalBalance = theTotalBalance;
    }
    int getAccountNumber()
    {
        return this->accountNumber;
    }
    bool validatePIN(int userPIN)
    {
        return this->PIN == userPIN;
    }
    double getAvailableBalance()
    {
        return this->availableBalance;
    }
    double getTotalBalance()
    {
        return this->totalBalance;
    }
    void credit(double amount)
    {
        this->totalBalance += amount;
    }
    void debit(double amount)
    {
        this->availableBalance -= amount;
        this->totalBalance -= amount;
    }
};