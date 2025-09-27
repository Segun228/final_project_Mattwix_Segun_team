#include "Report.h"
#include <fstream>
#include <iomanip>
#include <sstream>

namespace Reports {
/**
 * @brief Метод получения всех доходов
 * 
 * 
 * @return double 
 */
double Report::getTotalIncome() const {
    double total = 0;
    for (const auto& trans : transactions) {
        if (trans->getAmount() > 0) {
            total += trans->getAmount();
        }
    }
    return total;
}

/**
 * @brief Метод получения всех расходов
 * 
 * @return double 
*/
double Report::getTotalExpenses() const {
    double total = 0;
    for (const auto& trans : transactions) {
        if (trans->getAmount() < 0) {
            total += trans->getAmount();
        }
    }
    return total;
}

/**
 * @brief Получение текущего балланса
 * 
 * @return double 
 */
double Report::getNetBalance() const {
    return getTotalIncome() + getTotalExpenses();
}

/**
 * @brief Реализация метода вывода текстового отчета в терминал
 * 
 */
void TextReport::generate() const {
    std::cout << "=== " << title << " ===\n";
    std::cout << "Format: " << getFormat() << "\n";
    std::cout << "Transactions: " << transactions.size() << "\n\n";
    
    for (const auto& trans : transactions) {
        std::cout << *trans << "\n";
    }
    
    std::cout << "\n=== SUMMARY ===\n";
    std::cout << "Total Income: " << std::fixed << std::setprecision(2) << getTotalIncome() << "\n";
    std::cout << "Total Expenses: " << getTotalExpenses() << "\n";
    std::cout << "Net Balance: " << getNetBalance() << "\n";
}

/**
 * @brief Реализация метода вывода текстового отчета в файл
 * 
 */
void TextReport::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "=== " << title << " ===\n";
        file << "Format: " << getFormat() << "\n\n";
        
        for (const auto& trans : transactions) {
            file << *trans << "\n";
        }
        
        file << "\n=== SUMMARY ===\n";
        file << "Total Income: " << std::fixed << std::setprecision(2) << getTotalIncome() << "\n";
        file << "Total Expenses: " << getTotalExpenses() << "\n";
        file << "Net Balance: " << getNetBalance() << "\n";
        
        file.close();
        std::cout << "Report saved to: " << filename << std::endl;
    }
}

/**
 * @brief Реализация метода вывода CSV отчета в терминал
 * 
 */
void CSVReport::generate() const {
    std::cout << "Date,Type,Account,Category,Amount,Description\n";
    for (const auto& trans : transactions) {
        std::cout << trans->getFormattedDate() << ","
        << trans->getType() << ","
        << trans->getAccountName() << ","
        << trans->getCategoryName() << ","
        << trans->getAmount() << ","
        << "\"" << trans->getDescription() << "\"\n";
    }
}

/**
 * @brief Реализация метода вывода CSV отчета в файл
 * 
 */
void CSVReport::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "Date,Type,Account,Category,Amount,Description\n";
        for (const auto& trans : transactions) {
            file << trans->getFormattedDate() << ","
            << trans->getType() << ","
            << trans->getAccountName() << ","
            << trans->getCategoryName() << ","
            << trans->getAmount() << ","
            << "\"" << trans->getDescription() << "\"\n";
        }
        file.close();
        std::cout << "CSV report saved to: " << filename << std::endl;
    }
}

/**
 * @brief Реализация метода экранирования служебных символов JSON
 * 
 */
std::string JSONReport::escapeJson(const std::string& str) const {
    std::stringstream ss;
    for (char c : str) {
        switch (c) {
            case '"': ss << "\\\""; break;
            case '\\': ss << "\\\\"; break;
            case '\b': ss << "\\b"; break;
            case '\f': ss << "\\f"; break;
            case '\n': ss << "\\n"; break;
            case '\r': ss << "\\r"; break;
            case '\t': ss << "\\t"; break;
            default: ss << c; break;
        }
    }
    return ss.str();
}

/**
 * @brief Реализация метода вывода JSON отчета в терминал
 * 
 */
void JSONReport::generate() const {
    std::cout << "{\n";
    std::cout << "  \"title\": \"" << escapeJson(title) << "\",\n";
    std::cout << "  \"format\": \"" << getFormat() << "\",\n";
    std::cout << "  \"transactions\": [\n";
    
    for (size_t i = 0; i < transactions.size(); ++i) {
        const auto& trans = transactions[i];
        std::cout << "    {\n";
        std::cout << "      \"date\": \"" << trans->getFormattedDate() << "\",\n";
        std::cout << "      \"type\": \"" << trans->getType() << "\",\n";
        std::cout << "      \"account\": \"" << escapeJson(trans->getAccountName()) << "\",\n";
        std::cout << "      \"category\": \"" << escapeJson(trans->getCategoryName()) << "\",\n";
        std::cout << "      \"amount\": " << trans->getAmount() << ",\n";
        std::cout << "      \"description\": \"" << escapeJson(trans->getDescription()) << "\"\n";
        std::cout << "    }" << (i < transactions.size() - 1 ? "," : "") << "\n";
    }
    
    std::cout << "  ],\n";
    std::cout << "  \"summary\": {\n";
    std::cout << "    \"totalIncome\": " << getTotalIncome() << ",\n";
    std::cout << "    \"totalExpenses\": " << getTotalExpenses() << ",\n";
    std::cout << "    \"netBalance\": " << getNetBalance() << "\n";
    std::cout << "  }\n";
    std::cout << "}\n";
}

/**
 * @brief Реализация метода вывода JSON отчета в файл
 * 
 */
void JSONReport::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << "{\n";
        file << "  \"title\": \"" << escapeJson(title) << "\",\n";
        file << "  \"format\": \"" << getFormat() << "\",\n";
        file << "  \"transactions\": [\n";
        
        for (size_t i = 0; i < transactions.size(); ++i) {
            const auto& trans = transactions[i];
            file << "    {\n";
            file << "      \"date\": \"" << trans->getFormattedDate() << "\",\n";
            file << "      \"type\": \"" << trans->getType() << "\",\n";
            file << "      \"account\": \"" << escapeJson(trans->getAccountName()) << "\",\n";
            file << "      \"category\": \"" << escapeJson(trans->getCategoryName()) << "\",\n";
            file << "      \"amount\": " << std::fixed << std::setprecision(2) << trans->getAmount() << ",\n";
            file << "      \"description\": \"" << escapeJson(trans->getDescription()) << "\"\n";
            file << "    }" << (i < transactions.size() - 1 ? "," : "") << "\n";
        }
        
        file << "  ],\n";
        file << "  \"summary\": {\n";
        file << "    \"totalIncome\": " << getTotalIncome() << ",\n";
        file << "    \"totalExpenses\": " << getTotalExpenses() << ",\n";
        file << "    \"netBalance\": " << getNetBalance() << "\n";
        file << "  }\n";
        file << "}\n";
        
        file.close();
        std::cout << "JSON report saved to: " << filename << std::endl;
    }
}

} // namespace Reports