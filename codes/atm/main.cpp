#include <iostream>
#include "ATM.h"
using namespace std;

int main()
{
    Account *newCus1 = new Account(12345, 54321, 1000, 1200);
    Account *newCus2 = new Account(67890, 98765, 200, 200);
    Bank theBank;
    theBank.addCustomer(newCus1);
    theBank.addCustomer(newCus2);
    ATM theATM(theBank);
    theATM.Run();
}