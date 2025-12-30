// src/Infrastructure/Persistence/InMemoryExpenseRepository.cpp
#include "InMemoryExpenseRepository.h"

void InMemoryExpenseRepository::add(const Expense& expense) {
    Expense newExpense = expense;
    newExpense.setExpenseId(nextId++);
    expenses.push_back(newExpense);
}

std::vector<Expense> InMemoryExpenseRepository::getByBuilding(int buildingId) {
    std::vector<Expense> result;
    for (const auto& e : expenses) {
        if (e.getBuildingId() == buildingId) {
            result.push_back(e);
        }
    }
    return result;
}

std::vector<Expense> InMemoryExpenseRepository::getByBuildingAndMonth(
    int buildingId, int year, int month) {
    std::vector<Expense> result;
    for (const auto& e : expenses) {
        if (e.getBuildingId() != buildingId) continue;

        const std::string& date = e.getExpenseDate();
        if (date.size() < 7) continue;

        try {
            int expYear = std::stoi(date.substr(0, 4));
            int expMonth = std::stoi(date.substr(5, 2));
            if (expYear == year && expMonth == month) {
                result.push_back(e);
            }
        } catch (...) {
            // skip invalid date
        }
    }
    return result;
}