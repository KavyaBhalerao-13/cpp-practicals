
#include <iostream>
#include <string>
using namespace std;

class BankAccount
{
private:
    int accountNumber;
    double balance;

public:

    // Constructor
    BankAccount(int accNo, double bal)
    {
        accountNumber = accNo;
        balance = bal;
    }

    // Deposit function
    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance = balance + amount;
            cout << "Amount deposited successfully!" << endl;
        }
        else
        {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    // Withdraw function
    void withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance = balance - amount;
            cout << "Amount withdrawn successfully!" << endl;
        }
        else
        {
            cout << "Insufficient balance or invalid amount!" << endl;
        }
    }

    // Display function
    void display()
    {
        cout << "\nAccount Number: " << accountNumber << endl;
        cout << "Available Balance: " << balance << endl;
    }
};

int main()
{
    // Creating two objects
    BankAccount account1(101, 5000);
    BankAccount account2(102, 8000);

    cout << "----- Account 1 -----" << endl;
    account1.display();

    account1.deposit(2000);
    account1.withdraw(1000);
    account1.display();

    cout << "\n----- Account 2 -----" << endl;
    account2.display();

    account2.deposit(1500);
    account2.withdraw(500);
    account2.display();

    return 0;
}
