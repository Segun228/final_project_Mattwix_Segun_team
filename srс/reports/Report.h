#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "../transactions/Transaction.h"

namespace Reports {

class Report {
protected:
    std::string title;
    std::vector<std::shared_ptr<Transactions::Transaction>> transactions;

public:
    Report(const std::string& t) : title(t) {}
    virtual ~Report() = default;

    void addTransaction(std::shared_ptr<Transactions::Transaction> transaction) {
        transactions.push_back(transaction);
    }

    void setTransactions(const std::vector<std::shared_ptr<Transactions::Transaction>>& trans) {
        transactions = trans;
    }

    // Виртуальный метод генерации отчета
    virtual void generate() const = 0;
    
    // Виртуальный метод сохранения отчета
    virtual void saveToFile(const std::string& filename) const = 0;
    
    // Виртуальный метод получения формата
    virtual std::string getFormat() const = 0;

    // Общая статистика
    double getTotalIncome() const;
    double getTotalExpenses() const;
    double getNetBalance() const;
};

class TextReport : public Report {
public:
    TextReport(const std::string& t) : Report(t) {}

    void generate() const override;
    void saveToFile(const std::string& filename) const override;
    std::string getFormat() const override { return "TEXT"; }
};

class CSVReport : public Report {
public:
    CSVReport(const std::string& t) : Report(t) {}

    void generate() const override;
    void saveToFile(const std::string& filename) const override;
    std::string getFormat() const override { return "CSV"; }
};

class JSONReport : public Report {
private:
    std::string escapeJson(const std::string& str) const;

public:
    JSONReport(const std::string& t) : Report(t) {}

    void generate() const override;
    void saveToFile(const std::string& filename) const override;
    std::string getFormat() const override { return "JSON"; }
};

// Заглушка для XLSX - в реальном проекте использовалась бы библиотека типа libxlsxwriter
class XLSXReport : public Report {
public:
    XLSXReport(const std::string& t) : Report(t) {}

    void generate() const override;
    void saveToFile(const std::string& filename) const override;
    std::string getFormat() const override { return "XLSX"; }
};

} // namespace Reports