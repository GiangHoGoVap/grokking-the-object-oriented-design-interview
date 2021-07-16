#include <iostream>
#include "Transaction.h"
using namespace std;

class BalanceInquiry : public Transaction
{
public:
    BalanceInquiry(int userAccountNumber, Screen atmScreen, Bank atmBank) : Transaction(userAccountNumber, atmScreen, atmBank) {}
    void execute()
    {
        double availableBalance = Database().GetAvailableBalance(AccountNumber());
        double totalBalance = Database().GetTotalBalance(AccountNumber());
        UserScreen().showMessage("\nBalance Information:");
        UserScreen().showMessage(" - Available balance: ");
        UserScreen().showMessage(to_string(availableBalance));
        UserScreen().showMessage("\n - Total balance: ");
        UserScreen().showMessage(to_string(totalBalance));
        UserScreen().showMessage("");
    }
};