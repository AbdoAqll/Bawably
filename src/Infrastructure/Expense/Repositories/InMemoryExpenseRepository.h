// src/Infrastructure/Persistence/InMemoryExpenseRepository.h
#pragma once

#include "../Domain/Expense/ExpenseRepository.h"
#include "../Domain/Expense/Expense.h"
#include <vector>

class InMemoryExpenseRepository : public ExpenseRepository {
private:
    std::vector<Expense> expenses;
    int nextId = 1;

public:
    void add(const Expense& expense) override;
    std::vector<Expense> getByBuilding(int buildingId) override;
    std::vector<Expense> getByBuildingAndMonth(int buildingId, int year, int month) override;
};