#pragma once
#include <vector>
#include <memory>

// Шаблонная функция для поиска максимального элемента
template<typename T>
std::shared_ptr<T> findMaxBalance(const std::vector<std::shared_ptr<T>>& items) {
    if (items.empty()) return nullptr;
    
    std::shared_ptr<T> maxItem = items[0];
    for (const auto& item : items) {
        if (item && item->getBalance() > maxItem->getBalance()) {
            maxItem = item;
        }
    }
    return maxItem;
}

// Шаблонная функция для вычисления общего баланса
template<typename T>
double calculateTotalBalance(const std::vector<std::shared_ptr<T>>& items) {
    double total = 0.0;
    for (const auto& item : items) {
        if (item) {
            total += item->getBalance();
        }
    }
    return total;
}