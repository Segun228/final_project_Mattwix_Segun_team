#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Transaction { // заглушка
    double amount;  
    public:
        Transaction(double amt) : amount(amt) {}
        double getAmount() const { return amount; }

        // временный вывод
        friend std::ostream& operator<<(std::ostream& os, const Transaction& t) {
            os << (t.amount >= 0 ? "+" : "") << t.amount;
            return os;
        }
};

class Account {
    protected:
        std::string name;
        std::vector<Transaction> transactions;
    public: 
        Account(std::string n) : name(std::move(n)) {};
        virtual ~Account() = default;

        void addTransaction(const Transaction &t) {
            transactions.push_back(t);
        }

        virtual double getBalance() const {
            double sum = 0;
            for (const auto& t : transactions) { // TODO: add different transaction type support
                sum += t.getAmount();
            }

            return sum;
        }

        virtual void applyRules() = 0; // virtual method, that just exists

        friend std::ostream& operator<<(std::ostream &os, const Account &acc) {
            os << "Account: " << acc.name << ", Balance: " << acc.getBalance();
            return os;
        }
};

class CreditAccount : public Account {
    double creditLimit;

    public:
        CreditAccount(std::string n, double limit): Account(std::move(n)), creditLimit(limit) {};

        void applyRules() override {
            if (getBalance() < -creditLimit) {
                std::cout << "! Credit limit exceeded on  " << name << " !" << std::endl;
            }
        }
};

class DebitAccount : public Account {
    public:
        DebitAccount(std::string n): Account(std::move(n)) {};

        void applyRules() override {
            if (getBalance() < 0) {
                std::cout << "! Debit account  " << name << " cannot go negative!" << std::endl;
            }
        }
};

class SavingsAccount : public Account {
    double interestRate; // %

    public:
        SavingsAccount(std::string n, double rate): Account(std::move(n)), interestRate(rate) {};

        void applyRules() override {
            double interest = getBalance() * (interestRate / 100.0);
            if (interest > 0) {
                std::cout << "Interest added: " << interest << " on " << name << std::endl;
            }
        }
};

class InvestmentAccount : public Account {
    public:
        InvestmentAccount(std::string n): Account(std::move(n)) {};

        void applyRules() override {
            std::cout << "Investment account " << name << " fluctuates with the market (stub)." << std::endl;
        }
};

class User {
    std::string username;
    std::vector<std::unique_ptr<Account>> accounts;

    public: 
        User(std::string u) : username(std::move(u)) {}

        void addAccount(std::unique_ptr<Account> acc) {
            accounts.push_back(std::move(acc));
        }

        void showAccounts() const {
            std::cout << "User: " << username << "\n";
            for (const auto &acc : accounts) {
                std::cout << "  " << *acc << "\n";
            }
        }

        void applyAllRules() {
            for (auto &acc : accounts) {
                acc->applyRules();
            }
        }
};

// tests
int main () {
    User u("Alice");

    auto credit = std::make_unique<CreditAccount>("Credit-1", 500);
    credit->addTransaction(Transaction(-600)); // расход
    credit->addTransaction(Transaction(2000)); // доход

    auto savings = std::make_unique<SavingsAccount>("Savings-1", 5.0);
    savings->addTransaction(Transaction(5000));
    savings->addTransaction(Transaction(-100));

    auto debit = std::make_unique<DebitAccount>("Debit-1");
    debit->addTransaction(Transaction(200));
    debit->addTransaction(Transaction(-250)); // уход в минус

    auto invest = std::make_unique<InvestmentAccount>("Invest-1");
    invest->addTransaction(Transaction(1000));

    u.addAccount(std::move(credit));
    u.addAccount(std::move(savings));
    u.addAccount(std::move(debit));
    u.addAccount(std::move(invest));

    u.showAccounts();
    u.applyAllRules();

    /* Result: 
        User: Alice
            Account: Credit-1, Balance: 1400
            Account: Savings-1, Balance: 4900
            Account: Debit-1, Balance: -50
            Account: Invest-1, Balance: 1000
        Interest added: 245 on Savings-1
        ! Debit account  Debit-1 cannot go negative!
        Investment account Invest-1 fluctuates with the market (stub).
    */

    return 0;
} 