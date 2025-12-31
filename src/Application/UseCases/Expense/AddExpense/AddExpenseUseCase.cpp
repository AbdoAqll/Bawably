#include "AddExpenseUseCase.h"
#include "Domain/Shared/DomainException.h"
#include "Domain/Expense/Exceptions/InvalidBuildingIdForExpenseException.h"
#include "Domain/Expense/Exceptions/InvalidExpenseAmountException.h"
#include "Domain/Expense/Exceptions/InvalidExpenseDateException.h"

AddExpenseUseCase::AddExpenseUseCase(const shared_ptr<IExpenseRepository>& expenseRepository) {
    _expenseRepository = expenseRepository;
    UseCaseName = "AddExpense";
}

any AddExpenseUseCase::execute(const any& params) {
    auto args = any_cast<AddExpenseParams>(params);

    if (args.buildingId < 0) {
        throw InvalidBuildingIdForExpenseException(args.buildingId);
    }

    if (args.amount <= 0) {
        throw InvalidExpenseAmountException(args.amount);
    }

    if (args.expenseDate.empty()) {
        throw InvalidExpenseDateException("Expense date cannot be empty");
    }

    int expenseId = _expenseRepository->getNextId();
    Expense expense(expenseId, args.buildingId, args.category, args.amount, args.description, args.expenseDate);

    _expenseRepository->add(expense);

    return expenseId;
}
