#include "InMemoryExpenseRepository.h"

void InMemoryExpenseRepository::add(const Expense& expense) {
    expenses.push_back(expense);
}

vector<Expense> InMemoryExpenseRepository::getByBuilding(int buildingId) {
    vector<Expense> result;
    for (const auto& e : expenses) {
        if (e.getBuildingId() == buildingId) {
            result.push_back(e);
        }
    }
    return result;
}

vector<Expense> InMemoryExpenseRepository::getByBuildingAndMonth(int buildingId, int year, int month) {
    vector<Expense> result;
    for (const auto& e : expenses) {
        if (e.getBuildingId() != buildingId) continue;

        const string& date = e.getExpenseDate();
        if (date.size() < 7) continue;

        try {
            int expYear = stoi(date.substr(0, 4));
            int expMonth = stoi(date.substr(5, 2));
            if (expYear == year && expMonth == month) {
                result.push_back(e);
            }
        }
        catch (...) {
            // skip invalid date
        }
    }
    return result;
}

vector<Expense> InMemoryExpenseRepository::getAll() {
    return expenses;
}

int InMemoryExpenseRepository::getNextId() {
    return nextId++;
}