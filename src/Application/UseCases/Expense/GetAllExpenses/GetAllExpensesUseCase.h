#ifndef GETALLEXPENSESUSECASE_H
#define GETALLEXPENSESUSECASE_H

#include "Application/UseCases/IUseCase.h"
#include "Application/UseCases/Expense/Interfaces/IExpenseRepository.h"
#include <memory>

using namespace std;

class GetAllExpensesUseCase : public IUseCase {
private:
    shared_ptr<IExpenseRepository> _expenseRepository;

public:
    explicit GetAllExpensesUseCase(const shared_ptr<IExpenseRepository>& expenseRepository);
    any execute(const any& params = nullptr) override;
};

#endif // GETALLEXPENSESUSECASE_H
