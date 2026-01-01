#ifndef EXPENSE_CONTROLLER_H
#define EXPENSE_CONTROLLER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "Application/UseCases/IUseCase.h"

using namespace std;

class ExpenseController {
    unordered_map<string, shared_ptr<IUseCase>> useCases;

public:
    explicit ExpenseController(vector<shared_ptr<IUseCase>>& useCases);

    void executeForBuilding(int buildingId);
    void addExpense(int buildingId);
    void viewBuildingExpenses(int buildingId);

    void execute();
    void viewAllExpenses();
    void getExpensesByBuilding();
    void getExpensesByBuildingAndMonth();

    ~ExpenseController() = default;
};

#endif // EXPENSE_CONTROLLER_H