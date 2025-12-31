// src/Application/UseCases/Reports/GenerateMonthlyBuildingReportUseCase.h
#pragma once

#include "../../../UseCases/IUseCase.h"
#include "../../../../Domain/Report/MonthlyBuildingReport.h"
#include "../../../UseCases/Expense/Interfaces/IExpenseRepository.h"
#include "../../../UseCases/Apartment/Interfaces/IApartmentRepository.h"
#include "../../../UseCases/RentalContract/Interfaces/IRentalContractRepository.h"
#include "../../../UseCases/Building/Interfaces/IBuildingRepository.h"

using namespace std;

struct GenerateMonthlyReportParams {
    int buildingId;
    int year;
    int month;
};

class GenerateMonthlyBuildingReportUseCase : public IUseCase {
private:
    shared_ptr<IExpenseRepository> expenseRepo_;
    shared_ptr<IApartmentRepository> apartmentRepo_;
    shared_ptr<IRentalContractRepository> contractRepo_;
    shared_ptr<IBuildingRepository> buildingRepo_;

public:
    GenerateMonthlyBuildingReportUseCase(
        shared_ptr<IExpenseRepository> expenseRepo,
        shared_ptr<IApartmentRepository> apartmentRepo,
        shared_ptr<IRentalContractRepository> contractRepo,
        shared_ptr<IBuildingRepository> buildingRepo
    );

    any execute(const any& params = {}) override;
    MonthlyBuildingReport execute(int buildingId, int year, int month);
    ~GenerateMonthlyBuildingReportUseCase() override = default;
};