#include <iostream>
#include <memory>
#include <limits>
#include "src/users/User.h"
#include "src/accounts/Account.h"
#include "src/categories/Category.h"
#include "src/transactions/Transaction.h"
#include "src/reports/Report.h"
#include "src/utils/Utils.h"

/**
 * @brief Главная функция приложения Финансового Трекера
 * 
 * Эта функция создает демонстрационные объекты и запускает интерактивное меню
 * для демонстрации всех возможностей системы:
 * - Полиморфизм в иерархии счетов и категорий
 * - Перегрузка операторов (<<, +=, ==)
 * - Шаблонные функции для работы с коллекциями
 * - Генерация отчетов через полиморфизм
 * 
 * @return int Код завершения программы (0 - успешное завершение)
 */
int main() {
    std::cout << "\n=== Финансовый Трекер ===\n\n";
    
    User user("Alice");

    // 1. КЛАССЫ + НАСЛЕДОВАНИЕ + ПОЛИМОРФИЗМ
    user.addCategory(std::make_shared<ExpenseCategory>("Продукты", 5000));
    user.addCategory(std::make_shared<IncomeCategory>("Зарплата"));
    user.addCategory(std::make_shared<Category>("Разное"));

    user.addAccount(std::make_shared<DebitAccount>("Основной", 25000));
    user.addAccount(std::make_shared<CreditAccount>("Кредитка", 10000, 50000));
    user.addAccount(std::make_shared<SavingsAccount>("Накопления", 75000));

    int choice;
    while (true) {
        std::cout << "\n=== МЕНЮ ===\n";
        std::cout << "1. Показать счета\n";
        std::cout << "2. Показать категории\n";
        std::cout << "3. Демо операторов\n";
        std::cout << "4. Демо шаблонов\n";
        std::cout << "5. Отчет\n";
        std::cout << "0. Выход\n";
        std::cout << "Выбор: ";
        
        // Безопасное считывание числа
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод! Попробуйте снова.\n";
            continue;
        }
        std::cin.ignore(); // Очищаем буфер от символа новой строки

        if (choice == 0) {
            std::cout << "\nСпасибо за использование программы!\n";
            break;
        }

        switch (choice) {
        case 1: {
            std::cout << "\nСЧЕТА (ПОЛИМОРФИЗМ + ОПЕРАТОР <<):\n";
            for (const auto& acc : user.getAccounts()) {
                std::cout << *acc << "\n";  // Перегрузка оператора
            }
            break;
        }

        case 2: {
            std::cout << "\nКАТЕГОРИИ (ПОЛИМОРФИЗМ + ОПЕРАТОР <<):\n";
            for (const auto& cat : user.getCategories()) {
                std::cout << *cat << "\n";  // Перегрузка оператора
            }
            break;
        }

        case 3: {
            std::cout << "\nДЕМО ПЕРЕГРУЗКИ ОПЕРАТОРОВ:\n";
            
            auto acc1 = user.getAccounts()[0];
            auto acc2 = user.getAccounts()[1];
            
            std::cout << "До: " << *acc1 << "\n";
            std::cout << "До: " << *acc2 << "\n";
            
            *acc1 += 1000;  // Оператор +=
            
            std::cout << "После acc1 += 1000:\n";
            std::cout << *acc1 << "\n";
            
            // Оператор ==
            if (*acc1 == *acc1) {
                std::cout << "Оператор == работает!\n";
            }
            break;
        }

        case 4: {
            std::cout << "\nДЕМО ШАБЛОНОВ:\n";
            
            // Шаблонная функция findMaxBalance
            auto maxAcc = findMaxBalance(user.getAccounts());
            if (maxAcc) {
                std::cout << "Макс баланс: " << *maxAcc << "\n";
            }
            
            // Шаблонная функция calculateTotalBalance
            double total = calculateTotalBalance(user.getAccounts());
            std::cout << "Общий баланс: " << total << "\n";
            break;
        }

        case 5: {
            std::cout << "\nОТЧЕТЫ (ПОЛИМОРФИЗМ):\n";
            
            // Создаем тестовые транзакции
            auto account = user.getAccounts()[0];
            auto incomeCategory = user.getCategories()[1];  // Зарплата
            auto expenseCategory = user.getCategories()[0]; // Продукты

            std::vector<std::shared_ptr<Transactions::Transaction>> transactions;
            
            // Добавляем разные типы транзакций
            transactions.push_back(std::make_shared<Transactions::DepositTransaction>(
                50000, "Зарплата за месяц", incomeCategory, account));
                
            transactions.push_back(std::make_shared<Transactions::WithdrawalTransaction>(
                1500, "Продукты в магазине", expenseCategory, account));
                
            transactions.push_back(std::make_shared<Transactions::CompoundingTransaction>(
                10000, "Начисление процентов", 30, 5.0, nullptr, account));

            // Демонстрация разных форматов отчетов
            std::cout << "\n1. Текстовый отчет:\n";
            auto textReport = std::make_shared<Reports::TextReport>("Ежемесячный отчет");
            for(const auto& trans : transactions) {
                textReport->addTransaction(trans);
            }
            textReport->generate();
            
            std::cout << "\n2. CSV отчет:\n";
            auto csvReport = std::make_shared<Reports::CSVReport>("Ежемесячный отчет");
            for(const auto& trans : transactions) {
                csvReport->addTransaction(trans);
            }
            csvReport->generate();
            
            std::cout << "\n3. JSON отчет:\n";
            auto jsonReport = std::make_shared<Reports::JSONReport>("Ежемесячный отчет");
            for(const auto& trans : transactions) {
                jsonReport->addTransaction(trans);
            }
            jsonReport->generate();
            
            // Сохранение отчетов в файлы
            textReport->saveToFile("report.txt");
            csvReport->saveToFile("report.csv");
            jsonReport->saveToFile("report.json");
            break;
        }

        default:
            std::cout << "Неверный выбор! Попробуйте снова.\n";
            continue;
        }
        
        std::cout << "\nНажмите Enter для продолжения...";
        std::cin.get(); // Ждем нажатие Enter
    }

    return 0;
}
