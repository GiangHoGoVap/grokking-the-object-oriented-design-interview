#include <iostream>
#include "Transaction.h"
#include "Keypad.h"
#include "CashDispenser.h"
using namespace std;

class Withdrawal : public Transaction
{
private:
    double amount;
    Keypad keypad;
    CashDispenser cashDispenser;
    const int CANCELED = 6;
    int DisplayMenuOfAmounts()
    {
        int userChoice = 0;
        int amounts[] = {0, 20, 40, 60, 100, 200};
        while (userChoice == 0)
        {
            UserScreen().showMessage("\nWithdrawal options:");
            UserScreen().showMessage("1 - $20");
            UserScreen().showMessage("2 - $40");
            UserScreen().showMessage("3 - $60");
            UserScreen().showMessage("4 - $100");
            UserScreen().showMessage("5 - $200");
            UserScreen().showMessage("6 - Cancel transaction");
            UserScreen().showMessage("\nChoose a withdrawal option (1-6): ");
            string strInput = keypad.getInput();
            int input = stoi(strInput);
            switch (input)
            {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                userChoice = amounts[input];
                break;
            case 6:
                userChoice = CANCELED;
                break;
            default:
                UserScreen().showMessage("\nInvalid selection. Try again.");
                break;
            }
        }
        return userChoice;
    }

public:
    Withdrawal(int userAccountNumber, Screen atmScreen, Bank atmDatabase, Keypad atmKeypad, CashDispenser atmCashDispenser) : Transaction(userAccountNumber, atmScreen, atmDatabase)
    {
        this->keypad = atmKeypad;
        this->cashDispenser = atmCashDispenser;
    }
    void execute()
    {
        bool cashDispensed = false;
        bool transactionCanceled = false;
        do
        {
            int selection = DisplayMenuOfAmounts();
            if (selection != CANCELED)
            {
                amount = selection;
                double availableBalance = Database().GetAvailableBalance(AccountNumber());
                if (amount <= availableBalance)
                {
                    if (cashDispenser.canDispenseCash(amount))
                    {
                        Database().Debit(AccountNumber(), amount);
                        cashDispenser.dispenseCash(amount);
                        cashDispensed = true;
                        UserScreen().showMessage("\nPlease take your cash from the cash dispenser.");
                    }
                    else
                    {
                        UserScreen().showMessage("\nSufficient cash available int the ATM.");
                        UserScreen().showMessage("\n\nPlease choose a smaller amount.");
                    }
                }
                else
                {
                    UserScreen().showMessage("\nInsufficient cash available int your account.");
                    UserScreen().showMessage("\n\nPlease choose a smaller amount.");
                }
            }
            else
            {
                UserScreen().showMessage("\nCanceling transaction...");
                transactionCanceled = true;
            }
        } while (!cashDispensed && !transactionCanceled);
    }
};