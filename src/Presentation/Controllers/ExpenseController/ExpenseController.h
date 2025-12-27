// src/Presentation/Cli/ExpenseController.h
#pragma once

#include "../Application/UseCases/Expense/CreateExpenseUseCase.h"
#include "../Application/UseCases/Expense/GetExpensesByBuildingUseCase.h"
#include "../Application/UseCases/Expense/GetTotalExpensesByBuildingAndMonthUseCase.h"
#include <iostream>
#include <string>

class ExpenseController
{
private:
    CreateExpenseUseCase& createUseCase;
    GetExpensesByBuildingUseCase& listUseCase;
    GetTotalExpensesByBuildingAndMonthUseCase& totalUseCase;

public:
    // Constructor ياخد الـ Use Cases جاهزة (Dependency Injection)
    ExpenseController(
        CreateExpenseUseCase& create,
        GetExpensesByBuildingUseCase& list,
        GetTotalExpensesByBuildingAndMonthUseCase& total
    );

    // الدوال اللي هتتعامل مع المستخدم
    void showMenu() const;
    void handleAddExpense();
    void handleViewExpenses();
    void handleCalculateTotal();
};