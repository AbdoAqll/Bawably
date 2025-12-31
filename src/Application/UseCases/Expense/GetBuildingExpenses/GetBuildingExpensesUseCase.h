#ifndef GETBUILDINGEXPENSESUSECASE_H
#define GETBUILDINGEXPENSESUSECASE_H

#include "Application/UseCases/IUseCase.h"
#include "Application/UseCases/Expense/Interfaces/IExpenseRepository.h"
#include <memory>

using namespace std;

class GetBuildingExpensesUseCase : public IUseCase {
private:
    shared_ptr<IExpenseRepository> _expenseRepository;

public:
    explicit GetBuildingExpensesUseCase(const shared_ptr<IExpenseRepository>& expenseRepository);
    any execute(const any& params = nullptr) override;
};

#endif // GETBUILDINGEXPENSESUSECASE_H
