#ifndef ADDEXPENSEUSECASE_H
#define ADDEXPENSEUSECASE_H

#include "Application/UseCases/IUseCase.h"
#include "Application/UseCases/Expense/Interfaces/IExpenseRepository.h"
#include "Domain/Expense/ExpenseCategory.h"
#include <memory>
#include <string>

using namespace std;

struct AddExpenseParams {
    int buildingId;
    ExpenseCategory category;
    double amount;
    string expenseDate;
    string description;
};

class AddExpenseUseCase : public IUseCase {
private:
    shared_ptr<IExpenseRepository> _expenseRepository;

public:
    explicit AddExpenseUseCase(const shared_ptr<IExpenseRepository>& expenseRepository);
    any execute(const any& params = nullptr) override;
};

#endif // ADDEXPENSEUSECASE_H
