// src/Application/UseCases/Expense/CreateExpenseUseCase.h
#pragma once

#include "../../../Domain/Expense/Expense.h"
#include "../../../Domain/Expense/ExpenseRepository.h"

class CreateExpenseUseCase {
private:
    ExpenseRepository& repo;

public:
    explicit CreateExpenseUseCase(ExpenseRepository& repository);

    void execute(
        int buildingId,
        ExpenseCategory category,
        double amount,
        const std::string& date,
        const std::string& description = ""
    );
};