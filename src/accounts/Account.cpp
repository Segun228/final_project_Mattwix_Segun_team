/**
 * @file Account.cpp
 * @brief Реализация методов классов Account и его наследников
 */

#include "Account.h"
#include <iostream>

/**
 * @brief Конструктор базового класса Account
 * @param accName Название счета
 * @param initialBalance Начальный баланс счета
 */
Account::Account(const std::string& accName, double initialBalance)
    : name(accName), balance(initialBalance) {}

/**
 * @brief Внесение средств на счет
 * @param amount Сумма для внесения
 */
void Account::deposit(double amount) {
    balance += amount;
}

/**
 * @brief Снятие средств со счета
 * @param amount Сумма для снятия
 * @return true если операция успешна, false если недостаточно средств
 */
bool Account::withdraw(double amount) {
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

/**
 * @brief Получает название счета
 * @return Строка с названием счета
 */
std::string Account::getName() const {
    return name;
}

/**
 * @brief Получает текущий баланс счета
 * @return Текущий баланс
 */
double Account::getBalance() const {
    return balance;
}

// Перегрузка операторов
/**
 * @brief Оператор сравнения двух счетов
 * @param other Счет для сравнения
 * @return true если счета имеют одинаковое название
 */
bool Account::operator==(const Account& other) const {
    return name == other.name;
}

/**
 * @brief Оператор добавления суммы к балансу
 * @param amount Сумма для добавления
 * @return Ссылка на текущий счет
 */
Account& Account::operator+=(double amount) {
    deposit(amount);
    return *this;
}

/**
 * @brief Оператор вывода информации о счете в поток
 * @param os Поток вывода
 * @param account Счет для вывода
 * @return Поток вывода
 */
std::ostream& operator<<(std::ostream& os, const Account& account) {
    os << "[" << account.getType() << "] " << account.name 
       << " | Balance: " << account.balance;
    return os;
}

// Наследование - Debit Account
/**
 * @brief Конструктор класса DebitAccount
 * @param accName Название дебетового счета
 * @param initialBalance Начальный баланс счета
 */
DebitAccount::DebitAccount(const std::string& accName, double initialBalance)
    : Account(accName, initialBalance) {}

std::string DebitAccount::getType() const {
    return "DebitAccount";
}

// Наследование - Credit Account
CreditAccount::CreditAccount(const std::string& accName, double initialBalance, double limit)
    : Account(accName, initialBalance), creditLimit(limit) {}

bool CreditAccount::withdraw(double amount) {
    if (balance + creditLimit >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

std::string CreditAccount::getType() const {
    return "CreditAccount";
}

// Наследование - Savings Account
SavingsAccount::SavingsAccount(const std::string& accName, double initialBalance)
    : Account(accName, initialBalance) {}

std::string SavingsAccount::getType() const {
    return "SavingsAccount";
}
