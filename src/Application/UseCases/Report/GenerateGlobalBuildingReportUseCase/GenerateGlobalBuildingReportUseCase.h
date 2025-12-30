// src/Application/UseCases/Reports/GenerateGlobalBuildingReportUseCase.h
#pragma once

#include "../../../../Domain/Reports/GlobalBuildingReport.h"
#include "../../../../Domain/Expense/ExpenseRepository.h"
// #include "../../../../Domain/Building/BuildingRepository.h"
// #include "../../../../Domain/Apartment/ApartmentRepository.h"

class GenerateGlobalBuildingReportUseCase {
private:
    ExpenseRepository& expenseRepo_;
    // BuildingRepository& buildingRepo_;
    // ApartmentRepository& apartmentRepo_;

public:
    GenerateGlobalBuildingReportUseCase(ExpenseRepository& expenseRepo);

    GlobalBuildingReport execute(const std::string& generationDate = "");
};