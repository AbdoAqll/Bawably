#include "GetAllExpensesUseCase.h"
#include "Domain/Expense/Expense.h"
#include <vector>

GetAllExpensesUseCase::GetAllExpensesUseCase(const shared_ptr<IExpenseRepository>& expenseRepository) {
    _expenseRepository = expenseRepository;
    UseCaseName = "GetAllExpenses";
}

any GetAllExpensesUseCase::execute(const any& params) {
    vector<Expense> expenses = _expenseRepository->getAll();
    return expenses;
}
