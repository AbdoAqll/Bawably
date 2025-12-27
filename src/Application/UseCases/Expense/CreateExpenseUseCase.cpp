// src/Application/UseCases/Expense/CreateExpenseUseCase.cpp
#include "CreateExpenseUseCase.h"
#include <stdexcept>

CreateExpenseUseCase::CreateExpenseUseCase(ExpenseRepository& repository)
    : repo(repository) {}

void CreateExpenseUseCase::execute(
    int buildingId,
    ExpenseCategory category,
    double amount,
    const std::string& date,
    const std::string& description)
{
    if (buildingId <= 0) throw std::invalid_argument("Invalid building ID");
    if (amount <= 0) throw std::invalid_argument("Amount must be positive");
    if (date.empty()) throw std::invalid_argument("Date is required");

    Expense expense(0, buildingId, category, amount, description, date);
    repo.add(expense);
}