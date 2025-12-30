// src/Domain/Expense/ExpenseRepository.h
#pragma once

#include "Expense.h"
#include <vector>

class ExpenseRepository {
public:
    virtual ~ExpenseRepository() = default;

    virtual void add(const Expense& expense) = 0;
    virtual std::vector<Expense> getByBuilding(int buildingId) = 0;
    virtual std::vector<Expense> getByBuildingAndMonth(int buildingId, int year, int month) = 0;
};