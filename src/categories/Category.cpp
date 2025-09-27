/**
 * @file Category.cpp
 * @brief Реализация методов классов Category и его наследников
 */

#include "Category.h"

/**
 * @brief Конструктор базового класса Category
 * @param categoryName Название категории
 */
Category::Category(const std::string& categoryName) : name(categoryName) {}

/**
 * @brief Получает название категории
 * @return Строка с названием категории
 */
std::string Category::getName() const {
    return name;
}

// Перегрузка оператора ==
/**
 * @brief Оператор сравнения двух категорий
 * @param other Категория для сравнения
 * @return true если категории имеют одинаковое название
 */
bool Category::operator==(const Category& other) const {
    return name == other.name;
}

// Перегрузка оператора <<
/**
 * @brief Оператор вывода информации о категории в поток
 * @param os Поток вывода
 * @param category Категория для вывода
 * @return Поток вывода
 */
std::ostream& operator<<(std::ostream& os, const Category& category) {
    os << "[" << category.getType() << "] " << category.getName();
    if (category.getBudgetLimit() > 0) {
        os << " (Budget: " << category.getBudgetLimit() << ")";
    }
    return os;
}

// Категория расходов
/**
 * @brief Конструктор класса ExpenseCategory
 * @param name Название категории расходов
 * @param budget Лимит бюджета для категории
 */
ExpenseCategory::ExpenseCategory(const std::string& name, double budget)
    : Category(name), budgetLimit(budget) {}

// Категория доходов
/**
 * @brief Конструктор класса IncomeCategory
 * @param name Название категории доходов
 */
IncomeCategory::IncomeCategory(const std::string& name) : Category(name) {}
