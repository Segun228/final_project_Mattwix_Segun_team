#pragma once
#include <string>
#include <iostream>

// Базовый класс Account
/**
 * @brief Базовый абстрактный класс для всех типов счетов
 * 
 * Определяет общие свойства и интерфейс для всех счетов в системе.
 * Использует полиморфизм для обеспечения единообразного интерфейса
 * для различных типов счетов (дебетовые, кредитные, сберегательные).
 */
class Account {
protected:
    std::string name;
    double balance;

public:
    /**
     * @brief Конструктор базового класса Account
     * @param accName Название счета
     * @param initialBalance Начальный баланс счета
     */
    Account(const std::string& accName, double initialBalance);
    virtual ~Account() = default;

    /**
     * @brief Внесение средств на счет
     * @param amount Сумма для внесения
     */
    virtual void deposit(double amount);
    /**
     * @brief Снятие средств со счета
     * @param amount Сумма для снятия
     * @return true если операция успешна, false если недостаточно средств
     */
    virtual bool withdraw(double amount);
    /**
     * @brief Получает тип счета
     * @return Строка с названием типа счета
     */
    virtual std::string getType() const = 0; // Полиморфизм

    /**
     * @brief Получает название счета
     * @return Строка с названием счета
     */
    std::string getName() const;
    /**
     * @brief Получает текущий баланс счета
     * @return Текущий баланс
     */
    double getBalance() const;
    
    // Перегрузка операторов
    bool operator==(const Account& other) const;
    Account& operator+=(double amount);
    friend std::ostream& operator<<(std::ostream& os, const Account& account);
};

/**
 * @brief Класс дебетового счета
 * 
 * Представляет обычный дебетовый счет, на котором баланс
 * не может становиться отрицательным. Наследует от Account.
 * Демонстрирует принцип наследования в ООП.
 */
class DebitAccount : public Account {
public:
    DebitAccount(const std::string& accName, double initialBalance);
    std::string getType() const override;
};

/**
 * @brief Класс кредитного счета
 * 
 * Представляет кредитный счет с кредитным лимитом.
 * Позволяет балансу становиться отрицательным в пределах лимита.
 * Переопределяет метод withdraw() для учета кредитного лимита.
 */
class CreditAccount : public Account {
    double creditLimit;
public:
    CreditAccount(const std::string& accName, double initialBalance, double limit);
    bool withdraw(double amount) override;
    std::string getType() const override;
};

/**
 * @brief Класс сберегательного счета
 * 
 * Представляет сберегательный счет для накопления средств.
 * Обычно имеет ограниченное количество операций снятия.
 * Использует базовую реализацию методов Account.
 */
class SavingsAccount : public Account {
public:
    SavingsAccount(const std::string& accName, double initialBalance);
    std::string getType() const override;
};
