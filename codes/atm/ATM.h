#include <iostream>
#include "constants.h"
#include "Screen.h"
#include "Keypad.h"
#include "Bank.h"
#include "Transaction.h"
#include "CashDispenser.h"
#include "BalanceInquiry.h"
#include "Withdrawal.h"
#include "Deposit.h"
using namespace std;

class ATM
{
private:
    int atmID;
    bool userAuthenticated;
    Address location;
    Screen screen;
    Keypad keypad;
    Bank bank;
    CashDispenser cashDispenser;
    DepositSlot depositSlot;
    enum MenuOption
    {
        BALANCE_INQUIRY = 1,
        WITHDRAWAL = 2,
        DEPOSIT = 3,
        EXIT_ATM = 4
    };
    bool authenticateUser()
    {
        screen.showMessage("\nPlease enter your account number: ");
        int accountNumber = stoi(keypad.getInput());
        screen.showMessage("\nPlease enter PIN code: ");
        int PIN = stoi(keypad.getInput());
        userAuthenticated = bank.AuthenticateUser(accountNumber, PIN);
        if (userAuthenticated)
            this->atmID = accountNumber;
        else
            screen.showMessage("Invalid account number of PIN. Please try again.");
    }
    int DisplayMainMenu()
    {
        screen.showMessage("\nMain menu:");
        screen.showMessage("\n1 - View my balance");
        screen.showMessage("\n2 - Withdraw cash");
        screen.showMessage("\n3 - Deposit funds");
        screen.showMessage("\n4 - Exit");
        screen.showMessage("\nEnter a choice: ");
        int choice = stoi(keypad.getInput());
        return choice;
    }
    Transaction *createTransaction(int type)
    {
        Transaction *temp = NULL;
        switch ((MenuOption)type)
        {
        case BALANCE_INQUIRY:
            temp = new BalanceInquiry(atmID, screen, bank);
            break;
        case WITHDRAWAL:
            temp = new Withdrawal(atmID, screen, bank, keypad, cashDispenser);
            break;
        case DEPOSIT:
            temp = new Deposit(atmID, screen, bank, keypad, depositSlot);
            break;
        }
        return temp;
    }
    void performTransaction()
    {
        Transaction *currentTransaction;
        bool userExited = false;
        while (!userExited)
        {
            int mainMenuSelection = DisplayMainMenu();
            switch ((MenuOption)mainMenuSelection)
            {
            case BALANCE_INQUIRY:
            case WITHDRAWAL:
            case DEPOSIT:
                currentTransaction = createTransaction(mainMenuSelection);
                currentTransaction->execute();
                break;
            case EXIT_ATM:
                screen.showMessage("\nExiting the system...");
                userExited = true;
                break;
            default:
                screen.showMessage("\nYou did not enter a valid selection. Try again.");
                break;
            }
        }
    }

public:
    ATM(Bank theBank)
    {
        this->bank = theBank;
        this->userAuthenticated = false;
        this->atmID = 0;
    }
    void Run()
    {
        while (true)
        {
            while (!userAuthenticated)
            {
                screen.showMessage("\nWelcome!");
                authenticateUser();
            }
            performTransaction();
            this->userAuthenticated = false;
            this->atmID = 0;
            screen.showMessage("\nThank you! Goodbye!");
        }
    }
};