#include <iostream>
#include <stdexcept>
#include <string>
#include <iomanip>

// Base Custom Exception (inherits from std::runtime_error -> std::exception)
class BankException : public std::runtime_error {
public:
    explicit BankException(const std::string& msg) : std::runtime_error(msg) {}
};

// Custom Exception 1: Thrown for zero or negative transaction amounts
class InvalidAmount : public BankException {
public:
    explicit InvalidAmount(const std::string& msg) : BankException(msg) {}
};

// Custom Exception 2: Thrown when withdrawal exceeds available balance
class InsufficientFunds : public BankException {
public:
    explicit InsufficientFunds(const std::string& msg) : BankException(msg) {}
};

class BankAccount {
private:
    std::string holderName;
    double balance;

public:
    BankAccount(const std::string& name, double initialBalance)
        : holderName(name), balance(initialBalance) {}

    void withdraw(double amount) {
        if (amount <= 0) {
            throw InvalidAmount("Withdrawal amount must be greater than zero.");
        }
        if (amount > balance) {
            throw InsufficientFunds("Insufficient funds for this withdrawal.");
        }
        balance -= amount;
        std::cout << "  [Success] Withdrew Rs. " << amount << "\n";
    }

    double getBalance() const {
        return balance;
    }

    void displayBalance() const {
        std::cout << "  Current Balance (" << holderName << "): Rs. " << balance << "\n";
    }
};

void attemptWithdrawal(BankAccount& acc, double amount) {
    std::cout << "\nAttempting to withdraw Rs. " << amount << "...\n";
    try {
        acc.withdraw(amount);
    } catch (const InvalidAmount& e) {
        std::cout << "  [InvalidAmount Caught] " << e.what() << "\n";
    } catch (const InsufficientFunds& e) {
        std::cout << "  [InsufficientFunds Caught] " << e.what() << "\n";
    } catch (const BankException& e) {
        std::cout << "  [BankException Caught] " << e.what() << "\n";
    }
    acc.displayBalance();
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    BankAccount account("Kavya", 5000.00);
    std::cout << "=== Banking Transaction Demo ===\n";
    account.displayBalance();

    // 1. Successful transaction
    attemptWithdrawal(account, 1500.00);

    // 2. Failed transaction: Non-positive amount
    attemptWithdrawal(account, -200.00);

    // 3. Failed transaction: Exceeds balance
    attemptWithdrawal(account, 6000.00);

    return 0;
}