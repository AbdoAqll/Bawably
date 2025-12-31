#include "GetBuildingExpensesUseCase.h"
#include "Domain/Expense/Expense.h"
#include "Domain/Expense/Exceptions/InvalidBuildingIdForExpenseException.h"
#include <vector>

GetBuildingExpensesUseCase::GetBuildingExpensesUseCase(const shared_ptr<IExpenseRepository>& expenseRepository) {
    _expenseRepository = expenseRepository;
    UseCaseName = "GetBuildingExpenses";
}

any GetBuildingExpensesUseCase::execute(const any& params) {
    int buildingId = any_cast<int>(params);

    if (buildingId <= 0) {
        throw InvalidBuildingIdForExpenseException(buildingId);
    }

    vector<Expense> expenses = _expenseRepository->getByBuilding(buildingId);
    return expenses;
}
