// src/Application/UseCases/Reports/GenerateMonthlyBuildingReportUseCase.h
#pragma once

#include "../../../../Domain/Reports/MonthlyBuildingReport.h"
#include "../../../../Domain/Expense/ExpenseRepository.h"
// لو عندك ApartmentRepository و RentalContractRepository، ضيفهم هنا
// #include "../../../../Domain/Apartment/ApartmentRepository.h"
// #include "../../../../Domain/RentalContract/RentalContractRepository.h"

class GenerateMonthlyBuildingReportUseCase {
private:
    ExpenseRepository& expenseRepo_;
    // ApartmentRepository& apartmentRepo_;
    // RentalContractRepository& contractRepo_;

public:
    GenerateMonthlyBuildingReportUseCase(
        ExpenseRepository& expenseRepo
        // , ApartmentRepository& apartmentRepo, RentalContractRepository& contractRepo
    );

    MonthlyBuildingReport execute(int buildingId, int year, int month);
};