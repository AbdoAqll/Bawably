// src/Application/UseCases/Report/GenerateExpenseStatisticsUseCase/GenerateExpenseStatisticsUseCase.h
#pragma once

#include "../../../UseCases/IUseCase.h"
#include "../../../../Domain/Report/ExpenseStatistics.h"
#include "../../../UseCases/Building/Interfaces/IBuildingRepository.h"
#include "../../../UseCases/Expense/Interfaces/IExpenseRepository.h"

using namespace std;

struct GenerateExpenseStatsParams {
    int year;
    int month;
};

class GenerateExpenseStatisticsUseCase : public IUseCase {
private:
    shared_ptr<IBuildingRepository> buildingRepo_;
    shared_ptr<IExpenseRepository> expenseRepo_;

public:
    GenerateExpenseStatisticsUseCase(
        shared_ptr<IBuildingRepository> buildingRepo,
        shared_ptr<IExpenseRepository> expenseRepo
    );

    any execute(const any& params = {}) override;
    ExpenseStatistics execute(int year, int month);
    ~GenerateExpenseStatisticsUseCase() override = default;
};
