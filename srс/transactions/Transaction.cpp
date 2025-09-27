#include "Transaction.h"
#include "../categories/Category.h"
#include "../accounts/Account.h"
#include "../utils/DateUtils.h"

namespace Transactions {

/**
 * @brief Реализация класса обобщенной транзакции
 * 
 */
Transaction::Transaction(
    double amt, const std::string& desc,
    std::shared_ptr<Category> cat,
    std::shared_ptr<Account> acc
)
    : amount(amt), description(desc), category(cat), account(acc) {
    date = std::chrono::system_clock::now();
}

/**
 * @brief Category getter
 * 
 * @return std::string 
 */
std::string Transaction::getCategoryName() const { 
    return category ? category->getName() : "Uncategorized"; 
}

/**
 * @brief Account name getter
 * 
 * @return std::string 
 */
std::string Transaction::getAccountName() const { 
    return account ? account->getName() : "No Account"; 
}

/**
 * @brief Date of transaction getter
 * 
 * @return std::string 
 */
std::string Transaction::getFormattedDate() const {
    return DateUtils::formatTimePoint(date);
}

/**
 * @brief << operator overload
 * 
 * @param os 
 * @param t 
 * @return std::ostream& 
 */
std::ostream& operator<<(std::ostream& os, const Transaction& t) {
    os << t.getFormattedDate() << " | " << t.getType() << " | " 
    << t.getAccountName() << " | " << t.getCategoryName() << " | "
    << (t.getAmount() >= 0 ? "+" : "") << t.getAmount() << " | " << t.getDescription();
    return os;
}

/**
 * @brief Construct a new Deposit Transaction:: Deposit Transaction object
 * 
 * @param amt 
 * @param desc 
 * @param cat 
 * @param acc 
 */
DepositTransaction::DepositTransaction(
    double amt, const std::string& desc,
    std::shared_ptr<Category> cat,
    std::shared_ptr<Account> acc
)
    : Transaction(amt, desc, cat, acc) {}

/**
 * @brief Transaction execution method
 * 
 */
void DepositTransaction::execute() {
    std::cout << "Deposit executed: +" << amount << " to " 
    << getAccountName() << std::endl;
}

/**
 * @brief Rolling transaction back method
 * 
 */
void DepositTransaction::undo() {
    std::cout << "Deposit undone: -" << amount << " from " 
    << getAccountName() << std::endl;
}


/**
 * @brief Construct a new Withdrawal Transaction:: Withdrawal Transaction object
 * 
 * @param amt 
 * @param desc 
 * @param cat 
 * @param acc 
 */
WithdrawalTransaction::WithdrawalTransaction(
    double amt, const std::string& desc,
    std::shared_ptr<Category> cat,
    std::shared_ptr<Account> acc)
    : Transaction(-amt, desc, cat, acc) {} // Отрицательная сумма для списания

/**
 * @brief Withdrawal transaction execution method
 * 
 */
void WithdrawalTransaction::execute() {
    std::cout << "Withdrawal executed: " << amount << " from " 
    << getAccountName() << std::endl;
}

/**
 * @brief Withdrawal transaction rolling back method
 * 
 */
void WithdrawalTransaction::undo() {
    std::cout << "Withdrawal undone: +" << -amount << " to " 
    << getAccountName() << std::endl;
}

/**
 * @brief Construct a new Compounding Transaction:: Compounding Transaction object
 * 
 * @param amt 
 * @param desc 
 * @param p 
 * @param rate 
 * @param cat 
 * @param acc 
 */
CompoundingTransaction::CompoundingTransaction(
    double amt, const std::string& desc, 
    int p, double rate,
    std::shared_ptr<Category> cat,
    std::shared_ptr<Account> acc
)
    : Transaction(amt, desc, cat, acc), period(p), interestRate(rate) {}

/**
 * @brief Compounding transaction execution method
 * 
 */
void CompoundingTransaction::execute() {
    double interest = calculateCompoundInterest();
    std::cout << "Compounding executed: " << interest << " interest for " 
    << period << " days on " << getAccountName() << std::endl;
}

/**
 * @brief Compounding transaction rolling back method
 * 
 */
void CompoundingTransaction::undo() {
    std::cout << "Compounding undone on " << getAccountName() << std::endl;
}

/**
 * @brief Compounding transaction calculating compound method
 * 
 */
double CompoundingTransaction::calculateCompoundInterest() const {
    return amount * pow(1 + interestRate/100.0, period/365.0) - amount;
}

} // namespace Transactions