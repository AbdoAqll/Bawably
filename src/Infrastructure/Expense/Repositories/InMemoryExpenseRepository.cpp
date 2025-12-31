#include "InMemoryExpenseRepository.h"

InMemoryExpenseRepository::InMemoryExpenseRepository() {
    nextId = 1;

    // Add expenses for December 2025
    // Building 1 expenses
    Expense exp1(nextId++, 1, ExpenseCategory::Electricity, 350.0, "Monthly electricity bill", "2025-12-05");
    expenses.push_back(exp1);

    Expense exp2(nextId++, 1, ExpenseCategory::Cleaning, 200.0, "Building cleaning service", "2025-12-10");
    expenses.push_back(exp2);

    Expense exp3(nextId++, 1, ExpenseCategory::Plumbing, 150.0, "Pipe repair in common area", "2025-12-15");
    expenses.push_back(exp3);

    // Building 2 expenses
    Expense exp4(nextId++, 2, ExpenseCategory::Electricity, 280.0, "Monthly electricity bill", "2025-12-06");
    expenses.push_back(exp4);

    Expense exp5(nextId++, 2, ExpenseCategory::Security, 400.0, "Security guard service", "2025-12-01");
    expenses.push_back(exp5);

    Expense exp6(nextId++, 2, ExpenseCategory::Cleaning, 180.0, "Building cleaning service", "2025-12-12");
    expenses.push_back(exp6);

    // Building 3 expenses
    Expense exp7(nextId++, 3, ExpenseCategory::Electricity, 420.0, "Monthly electricity bill", "2025-12-07");
    expenses.push_back(exp7);

    Expense exp8(nextId++, 3, ExpenseCategory::Other, 500.0, "Elevator maintenance", "2025-12-20");
    expenses.push_back(exp8);

    // Previous month expenses (November 2025)
    Expense exp9(nextId++, 1, ExpenseCategory::Electricity, 320.0, "Monthly electricity bill", "2025-11-05");
    expenses.push_back(exp9);

    Expense exp10(nextId++, 2, ExpenseCategory::Electricity, 270.0, "Monthly electricity bill", "2025-11-06");
    expenses.push_back(exp10);

    Expense exp11(nextId++, 3, ExpenseCategory::Electricity, 390.0, "Monthly electricity bill", "2025-11-07");
    expenses.push_back(exp11);
}

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