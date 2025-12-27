#pragma once

#include "../../Domain/Expense/Expense.h"
#include "../../Domain/Expense/ExpenseRepository.h"
#include <vector>

class GetExpensesByBuildingUseCase {
private:
    ExpenseRepository& repo;

public:
    explicit GetExpensesByBuildingUseCase(ExpenseRepository& repository);

    std::vector<Expense> execute(int buildingId);
};