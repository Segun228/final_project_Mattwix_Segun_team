#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../accounts/Account.h"
#include "../categories/Category.h"

/**
 * @brief Класс пользователя системы
 *
 * Представляет пользователя финансовой системы, который может иметь
 * несколько счетов и категорий для классификации транзакций.
 * Управляет списками счетов и категорий через умные указатели.
 */
class User {
    std::string name;                                    ///< Имя пользователя
    std::vector<std::shared_ptr<Account>> accounts;      ///< Список счетов пользователя
    std::vector<std::shared_ptr<Category>> categories;   ///< Список категорий пользователя

public:
    /**
     * @brief Конструктор класса User
     * @param username Имя пользователя
     */
    User(const std::string& username);

    /**
     * @brief Добавляет новый счет пользователю
     * @param acc Умный указатель на счет
     */
    void addAccount(std::shared_ptr<Account> acc);
    /**
     * @brief Добавляет новую категорию пользователю
     * @param cat Умный указатель на категорию
     */
    void addCategory(std::shared_ptr<Category> cat);

    /**
     * @brief Получает список всех счетов пользователя
     * @return Константная ссылка на вектор умных указателей на счета
     */
    const std::vector<std::shared_ptr<Account>>& getAccounts() const;
    /**
     * @brief Получает список всех категорий пользователя
     * @return Константная ссылка на вектор умных указателей на категории
     */
    const std::vector<std::shared_ptr<Category>>& getCategories() const;
    /**
     * @brief Получает имя пользователя
     * @return Строка с именем пользователя
     */
    std::string getName() const;
};