#ifndef GETEXPENSESBYBUILDINGANDMONTHUSECASE_H
#define GETEXPENSESBYBUILDINGANDMONTHUSECASE_H

#include "Application/UseCases/IUseCase.h"
#include "Application/UseCases/Expense/Interfaces/IExpenseRepository.h"
#include <memory>

using namespace std;

struct GetExpensesByBuildingAndMonthParams {
    int buildingId;
    int year;
    int month;
};

struct GetExpensesByBuildingAndMonthResult {
    vector<Expense> expenses;
    double totalAmount;
};

class GetExpensesByBuildingAndMonthUseCase : public IUseCase {
private:
    shared_ptr<IExpenseRepository> _expenseRepository;

public:
    explicit GetExpensesByBuildingAndMonthUseCase(const shared_ptr<IExpenseRepository>& expenseRepository);
    any execute(const any& params = nullptr) override;
};

#endif // GETEXPENSESBYBUILDINGANDMONTHUSECASE_H
