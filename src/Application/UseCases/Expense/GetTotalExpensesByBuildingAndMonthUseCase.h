// src/Application/UseCases/Expense/GetTotalExpensesByBuildingAndMonthUseCase.h
#pragma once

#include "../../../Domain/Expense/Expense.h"
#include "../../../Domain/Expense/ExpenseRepository.h"

class GetTotalExpensesByBuildingAndMonthUseCase {
private:
    ExpenseRepository& repo;

public:
    explicit GetTotalExpensesByBuildingAndMonthUseCase(ExpenseRepository& repository);

    double execute(int buildingId, int year, int month);
};