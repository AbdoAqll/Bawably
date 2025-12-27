#include "GetExpensesByBuildingUseCase.h"

GetExpensesByBuildingUseCase::GetExpensesByBuildingUseCase(ExpenseRepository& repository)
    : repo(repository) {}

std::vector<Expense> GetExpensesByBuildingUseCase::execute(int buildingId) {
    return repo.getByBuilding(buildingId);
}