#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <chrono>
#include <vector>


class Category;
class Account;

namespace Transactions {

/**
 * @brief Интерфейс класса обобщенной транзакции
 * 
 */
class Transaction {
protected:
    double amount;
    std::string description;
    std::chrono::system_clock::time_point date;
    std::shared_ptr<Category> category;
    std::shared_ptr<Account> account;

public:
    Transaction(
        double amt, const std::string& desc, 
        std::shared_ptr<Category> cat = nullptr,
        std::shared_ptr<Account> acc = nullptr
    );
    virtual ~Transaction() = default;

    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::string getType() const = 0;


    double getAmount() const { return amount; }
    std::string getDescription() const { return description; }
    auto getDate() const { return date; }
    std::string getCategoryName() const;
    std::string getAccountName() const;
    std::string getFormattedDate() const;

    friend std::ostream& operator<<(std::ostream& os, const Transaction& t);
};

/**
 * @brief Интерфейс класса транзакции пополнения
 * 
 */
class DepositTransaction : public Transaction {
public:
    DepositTransaction(
        double amt, const std::string& desc,
        std::shared_ptr<Category> cat = nullptr,
        std::shared_ptr<Account> acc = nullptr
    );

    void execute() override;
    void undo() override;
    std::string getType() const override { return "DEPOSIT"; }
};

/**
 * @brief Интерфейс класса транзакции снятия
 * 
 */
class WithdrawalTransaction : public Transaction {
public:
    WithdrawalTransaction(
        double amt, const std::string& desc,
        std::shared_ptr<Category> cat = nullptr,
        std::shared_ptr<Account> acc = nullptr
    );

    void execute() override;
    void undo() override;
    std::string getType() const override { return "WITHDRAWAL"; }
};

/**
 * @brief Интерфейс класса транзакции компаудирования
 * 
 */
class CompoundingTransaction : public Transaction {
private:
    int period;
    double interestRate;

public:
    CompoundingTransaction(
        double amt, const std::string& desc, int p, double rate,
        std::shared_ptr<Category> cat = nullptr,
        std::shared_ptr<Account> acc = nullptr
    );

    void execute() override;
    void undo() override;
    std::string getType() const override { return "COMPOUNDING"; }
    
    double calculateCompoundInterest() const;
};

}