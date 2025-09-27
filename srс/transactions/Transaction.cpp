#include "Transaction.h"
#include "../categories/Category.h"
#include "../accounts/Account.h"
#include "../utils/DateUtils.h"

namespace Transactions {

Transaction::Transaction(
    double amt, const std::string& desc,
    std::shared_ptr<Category> cat,
    std::shared_ptr<Account> acc
)
    : amount(amt), description(desc), category(cat), account(acc) {
    date = std::chrono::system_clock::now();
}

std::string Transaction::getCategoryName() const { 
    return category ? category->getName() : "Uncategorized"; 
}

std::string Transaction::getAccountName() const { 
    return account ? account->getName() : "No Account"; 
}

std::string Transaction::getFormattedDate() const {
    return DateUtils::formatTimePoint(date);
}

std::ostream& operator<<(std::ostream& os, const Transaction& t) {
    os << t.getFormattedDate() << " | " << t.getType() << " | " 
    << t.getAccountName() << " | " << t.getCategoryName() << " | "
    << (t.getAmount() >= 0 ? "+" : "") << t.getAmount() << " | " << t.getDescription();
    return os;
}


DepositTransaction::DepositTransaction(
    double amt, const std::string& desc,
    std::shared_ptr<Category> cat,
    std::shared_ptr<Account> acc
)
    : Transaction(amt, desc, cat, acc) {}

void DepositTransaction::execute() {
    std::cout << "Deposit executed: +" << amount << " to " 
    << getAccountName() << std::endl;
}

void DepositTransaction::undo() {
    std::cout << "Deposit undone: -" << amount << " from " 
    << getAccountName() << std::endl;
}

// WithdrawalTransaction реализация
WithdrawalTransaction::WithdrawalTransaction(
    double amt, const std::string& desc,
    std::shared_ptr<Category> cat,
    std::shared_ptr<Account> acc)
    : Transaction(-amt, desc, cat, acc) {} // Отрицательная сумма для списания

void WithdrawalTransaction::execute() {
    std::cout << "Withdrawal executed: " << amount << " from " 
    << getAccountName() << std::endl;
}

void WithdrawalTransaction::undo() {
    std::cout << "Withdrawal undone: +" << -amount << " to " 
    << getAccountName() << std::endl;
}

// CompoundingTransaction реализация
CompoundingTransaction::CompoundingTransaction(
    double amt, const std::string& desc, 
    int p, double rate,
    std::shared_ptr<Category> cat,
    std::shared_ptr<Account> acc
)
    : Transaction(amt, desc, cat, acc), period(p), interestRate(rate) {}

void CompoundingTransaction::execute() {
    double interest = calculateCompoundInterest();
    std::cout << "Compounding executed: " << interest << " interest for " 
    << period << " days on " << getAccountName() << std::endl;
}

void CompoundingTransaction::undo() {
    std::cout << "Compounding undone on " << getAccountName() << std::endl;
}

double CompoundingTransaction::calculateCompoundInterest() const {
    // Простая формула сложного процента для демонстрации
    return amount * pow(1 + interestRate/100.0, period/365.0) - amount;
}

} // namespace Transactions