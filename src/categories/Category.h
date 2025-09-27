#pragma once
#include <string>
#include <iostream>

/**
 * @brief Базовый класс для всех типов категорий транзакций
 * 
 * Определяет общие свойства всех категорий. Использует полиморфизм
 * для обеспечения единообразного интерфейса для доходов и расходов.
 */
class Category {
protected:
    std::string name;
    
public:
    Category(const std::string& categoryName);
    virtual ~Category() = default;
    
    std::string getName() const;
    
    // Виртуальные методы (ПОЛИМОРФИЗМ)
    virtual std::string getType() const { return "Category"; }
    virtual double getBudgetLimit() const { return 0.0; }
    
    // Перегрузка операторов
    bool operator==(const Category& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Category& category);
};

/**
 * @brief Класс категории расходов
 * 
 * Представляет категорию для расходов с определенным бюджетом.
 * Позволяет контролировать лимит расходов по категориям.
 */
class ExpenseCategory : public Category {
private:
    double budgetLimit;
    
public:
    ExpenseCategory(const std::string& name, double budget);
    
    double getBudgetLimit() const override { return budgetLimit; }
    std::string getType() const override { return "ExpenseCategory"; }
};

/**
 * @brief Класс категории доходов
 * 
 * Представляет категорию для доходов. Не имеет лимита,
 * так как доходы обычно не ограничиваются.
 */
class IncomeCategory : public Category {
public:
    IncomeCategory(const std::string& name);
    
    std::string getType() const override { return "IncomeCategory"; }
};
