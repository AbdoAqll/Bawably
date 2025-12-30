// src/Application/UseCases/Expense/GetTotalExpensesByBuildingAndMonthUseCase.cpp
#include "GetTotalExpensesByBuildingAndMonthUseCase.h"

GetTotalExpensesByBuildingAndMonthUseCase::GetTotalExpensesByBuildingAndMonthUseCase(
    ExpenseRepository& repository)
    : repo(repository) {}

double GetTotalExpensesByBuildingAndMonthUseCase::execute(int buildingId, int year, int month) {
    auto expenses = repo.getByBuildingAndMonth(buildingId, year, month);
    double total = 0.0;
    for (const auto& e : expenses) {
        total += e.getAmount();
    }
    return total;
}