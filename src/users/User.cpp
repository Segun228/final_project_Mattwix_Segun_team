/**
 * @file User.cpp
 * @brief Реализация методов класса User
 */

#include "User.h"

/**
 * @brief Конструктор класса User
 * @param username Имя пользователя
 */
User::User(const std::string& username) : name(username) {}

/**
 * @brief Добавляет новый счет пользователю
 * @param acc Умный указатель на счет
 */
void User::addAccount(std::shared_ptr<Account> acc) {
    accounts.push_back(acc);
}

/**
 * @brief Добавляет новую категорию пользователю
 * @param cat Умный указатель на категорию
 */
void User::addCategory(std::shared_ptr<Category> cat) {
    categories.push_back(cat);
}

/**
 * @brief Получает список всех счетов пользователя
 * @return Константная ссылка на вектор умных указателей на счета
 */
const std::vector<std::shared_ptr<Account>>& User::getAccounts() const {
    return accounts;
}

/**
 * @brief Получает список всех категорий пользователя
 * @return Константная ссылка на вектор умных указателей на категории
 */
const std::vector<std::shared_ptr<Category>>& User::getCategories() const {
    return categories;
}

/**
 * @brief Получает имя пользователя
 * @return Строка с именем пользователя
 */
std::string User::getName() const {
    return name;
}