# Финансовый Трекер

Консольное приложение для управления личными финансами, реализованное на C++ с использованием принципов ООП.

## Структура проекта

```bash
FinanceTracker/
├── main.cpp              # Главный файл с CLI-интерфейсом
├── src/
│   ├── accounts/         # Управление счетами
│   ├── categories/       # Категории транзакций
│   ├── transactions/     # Система транзакций
│   ├── reports/         # Генерация отчётов
│   ├── users/           # Управление пользователями
│   └── utils/           # Вспомогательные функции
```

## Основные классы и их методы

### Account (Счета)

#### Базовый класс `Account`

Поля:

- `name`: `std::string` - название счёта
- `balance`: `double` - текущий баланс

Методы:

- `Account(const std::string& accName, double initialBalance)`: конструктор
- `virtual void deposit(double amount)`: внесение средств на счёт
- `virtual bool withdraw(double amount)`: снятие средств (возвращает false при недостатке средств)
- `double getBalance() const`: получение текущего баланса
- `std::string getName() const`: получение названия счёта
- `virtual std::string getType() const = 0`: получение типа счёта (чисто виртуальный метод)

#### Наследники (аккаунты)

##### `DebitAccount`

- Конструктор: `DebitAccount(const std::string& accName, double initialBalance)`
- Особенности: не позволяет уходить в минус (баланс всегда >= 0)

##### `CreditAccount`

Дополнительные поля:

- `creditLimit`: `double` - кредитный лимит

Методы:

- Конструктор: `CreditAccount(const std::string& accName, double initialBalance, double limit)`
- Переопределён: `bool withdraw(double amount)` - позволяет уходить в минус до кредитного лимита

##### `SavingsAccount`

- Конструктор: `SavingsAccount(const std::string& accName, double initialBalance)`
- Особенности: предназначен для накоплений, может иметь особые условия по процентам

### Category (Категории)

#### Базовый класс `Category`

Поля:

- `name`: `std::string` - название категории

Методы:

- `Category(const std::string& categoryName)`: конструктор
- `std::string getName() const`: получение названия
- `virtual std::string getType() const`: получение типа категории
- `virtual double getBudgetLimit() const`: получение лимита бюджета (по умолчанию 0.0)

#### Наследники (категории)

##### `ExpenseCategory`

Дополнительные поля:

- `budgetLimit`: `double` - лимит расходов по категории

Методы:

- Конструктор: `ExpenseCategory(const std::string& name, double budget)`
- Переопределён: `double getBudgetLimit() const` - возвращает установленный лимит

##### `IncomeCategory`

- Конструктор: `IncomeCategory(const std::string& name)`
- Особенности: не имеет лимита бюджета

### Transaction (Транзакции)

#### Базовый класс `Transaction`

Поля:

- `amount`: `double` - сумма транзакции
- `description`: `std::string` - описание
- `date`: `std::chrono::system_clock::time_point` - дата и время
- `category`: `std::shared_ptr<Category>` - категория
- `account`: `std::shared_ptr<Account>` - связанный счёт

Методы:

- Конструктор: `Transaction(double amt, const std::string& desc, std::shared_ptr<Category> cat, std::shared_ptr<Account> acc)`
- `virtual void execute() = 0`: выполнение транзакции
- `virtual void undo() = 0`: отмена транзакции
- `virtual std::string getType() const = 0`: тип транзакции
- `double getAmount() const`: получение суммы
- `std::string getDescription() const`: получение описания
- `std::string getFormattedDate() const`: получение отформатированной даты

#### Наследники (транзакции)

##### `DepositTransaction`

- Конструктор: `DepositTransaction(double amt, const std::string& desc, std::shared_ptr<Category> cat, std::shared_ptr<Account> acc)`
- Особенности: сумма всегда положительная, увеличивает баланс счёта

##### `WithdrawalTransaction`

- Конструктор: `WithdrawalTransaction(double amt, const std::string& desc, std::shared_ptr<Category> cat, std::shared_ptr<Account> acc)`
- Особенности: сумма конвертируется в отрицательную, уменьшает баланс счёта

##### `CompoundingTransaction`

Дополнительные поля:

- `period`: `int` - период в днях
- `interestRate`: `double` - процентная ставка

Методы:

- Конструктор: `CompoundingTransaction(double amt, const std::string& desc, int p, double rate, std::shared_ptr<Category> cat, std::shared_ptr<Account> acc)`
- `double calculateCompoundInterest() const`: расчёт сложных процентов

### Report (Отчёты)

#### Базовый класс `Report`

Поля:

- `title`: `std::string` - заголовок отчёта
- `transactions`: `std::vector<std::shared_ptr<Transaction>>` - список транзакций

Методы:

- Конструктор: `Report(const std::string& t)`
- `void addTransaction(std::shared_ptr<Transaction> transaction)`: добавление транзакции
- `virtual void generate() const = 0`: генерация отчёта
- `virtual void saveToFile(const std::string& filename) const = 0`: сохранение в файл
- `virtual std::string getFormat() const = 0`: получение формата
- `double getTotalIncome() const`: подсчёт суммы доходов
- `double getTotalExpenses() const`: подсчёт суммы расходов
- `double getNetBalance() const`: получение общего баланса

#### Наследники (отчеты)

##### `TextReport`

- Особенности: генерирует отчёт в человекочитаемом текстовом формате

##### `CSVReport`

- Особенности: создаёт файл с разделителями-запятыми, удобный для импорта в Excel

##### `JSONReport`

Дополнительные методы:

- `std::string escapeJson(const std::string& str) const`: экранирование спецсимволов
- Особенности: создаёт структурированный JSON-документ

### User (Пользователь)

#### Класс `User`

Поля:

- `name`: `std::string` - имя пользователя
- `accounts`: `std::vector<std::shared_ptr<Account>>` - список счетов
- `categories`: `std::vector<std::shared_ptr<Category>>` - список категорий

Методы:

- Конструктор: `User(const std::string& username)`
- `void addAccount(std::shared_ptr<Account> acc)`: добавление счёта
- `void addCategory(std::shared_ptr<Category> cat)`: добавление категории
- `const std::vector<std::shared_ptr<Account>>& getAccounts() const`: получение списка счетов
- `const std::vector<std::shared_ptr<Category>>& getCategories() const`: получение списка категорий
- `std::string getName() const`: получение имени пользователя

## CLI-интерфейс

Главное меню программы предоставляет следующие опции:

- `1` **Показать счета**
  - Выводит список всех счетов пользователя
  - Отображает тип счёта, название и текущий баланс

- `2` **Показать категории**
  - Выводит список всех категорий
  - Для категорий расходов показывает лимит бюджета

- `3` **Демо операторов**
  - Демонстрация перегрузки операторов
  - Примеры операций со счетами

- `4` **Демо шаблонов**
  - Демонстрация работы шаблонных функций
  - Поиск счета с максимальным балансом
  - Подсчёт общего баланса

- `5` **Отчет**
  - Генерация отчёта о транзакциях
  - Вывод общей статистики

- `0` **Выход**
  - Завершение работы программы

## Сборка и запуск

```bash
# Сборка проекта
make

# Запуск программы
./FinanceTracker
```
