#include <iostream>
#include "Transaction.h"
#include "Screen.h"
#include "Bank.h"
#include "DepositSlot.h"
#include "Keypad.h"
using namespace std;

class Deposit : public Transaction
{
private:
    double amount;
    Keypad keypad;
    DepositSlot depositSlot;
    const int CANCELED = 0;
    double PromptForDepositAmount()
    {
        UserScreen().showMessage("\nPlease input a deposit amount in CENTS (or 0 to cancel): ");
        int input = stoi(keypad.getInput());
        if (input == CANCELED)
            return CANCELED;
        else
            return input / 100;
    }

public:
    Deposit(int userAccountNumber, Screen atmScreen, Bank atmDatabase, Keypad atmKeypad, DepositSlot atmDepositSlot) : Transaction(userAccountNumber, atmScreen, atmDatabase)
    {
        this->keypad = atmKeypad;
        this->depositSlot = atmDepositSlot;
    }
    void execute()
    {
        amount = PromptForDepositAmount();
        if (amount != CANCELED)
        {
            UserScreen().showMessage("\nPlease insert a deposit envelope containing ");
            UserScreen().showMessage(to_string(amount));
            UserScreen().showMessage(" in the deposit slot.");
            bool envelopeReceived = depositSlot.IsDepositEnveloped();
            if (envelopeReceived)
            {
                UserScreen().showMessage("\nYour envelope has been received.");
                UserScreen().showMessage("\nThe money just deposited will not be available until we verify the amount of any enclosed cash, and any enclosed checks clear.");
                Database().Credit(AccountNumber(), amount);
            }
            else
            {
                UserScreen().showMessage("\nYou did not insert an envelope, so the ATM has canceled your transaction.");
            }
        }
        else
        {
            UserScreen().showMessage("\nCanceling transaction...");
        }
    }
};