// src/Application/UseCases/Reports/GenerateGlobalBuildingReportUseCase.h
#pragma once

#include "../../../UseCases/IUseCase.h"
#include "../../../../Domain/Report/GlobalBuildingReport.h"
#include "../../../UseCases/Expense/Interfaces/IExpenseRepository.h"
#include "../../../UseCases/Building/Interfaces/IBuildingRepository.h"
#include "../../../UseCases/Apartment/Interfaces/IApartmentRepository.h"
#include "../../../UseCases/RentalContract/Interfaces/IRentalContractRepository.h"

using namespace std;

struct GenerateGlobalReportParams {
    int year;
    int month;
};

class GenerateGlobalBuildingReportUseCase : public IUseCase {
private:
    shared_ptr<IExpenseRepository> expenseRepo_;
    shared_ptr<IBuildingRepository> buildingRepo_;
    shared_ptr<IApartmentRepository> apartmentRepo_;
    shared_ptr<IRentalContractRepository> contractRepo_;

public:
    GenerateGlobalBuildingReportUseCase(
        shared_ptr<IExpenseRepository> expenseRepo,
        shared_ptr<IBuildingRepository> buildingRepo,
        shared_ptr<IApartmentRepository> apartmentRepo,
        shared_ptr<IRentalContractRepository> contractRepo);

    any execute(const any& params = {}) override;
    GlobalBuildingReport execute(int year, int month);
    ~GenerateGlobalBuildingReportUseCase() override = default;
};