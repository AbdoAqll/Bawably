// src/Application/UseCases/Reports/GenerateMonthlyBuildingReportUseCase.cpp
#include "GenerateMonthlyBuildingReportUseCase.h"
#include <stdexcept>

GenerateMonthlyBuildingReportUseCase::GenerateMonthlyBuildingReportUseCase(
    ExpenseRepository& expenseRepo
     , ApartmentRepository& apartmentRepo, RentalContractRepository& contractRepo
)
    : expenseRepo_(expenseRepo)
     , apartmentRepo_(apartmentRepo), contractRepo_(contractRepo)
{
}

MonthlyBuildingReport GenerateMonthlyBuildingReportUseCase::execute(int buildingId, int year, int month) {
    if (buildingId <= 0) throw std::invalid_argument("Building ID must be positive");

    MonthlyBuildingReport report(buildingId, year, month);

    auto expenses = expenseRepo_.getByBuildingAndMonth(buildingId, year, month);
    double totalExpenses = 0.0;
    for (const auto& e : expenses) {
        totalExpenses += e.getAmount();
    }
    report.setTotalExpenses(totalExpenses);

    report.setTotalApartments(apartmentRepo_.countByBuilding(buildingId));

    report.setRentedApartments(contractRepo_.countActiveForBuilding(buildingId, year, month));

    report.setTotalRentIncome(contractRepo_.calculateTotalRentForBuilding(buildingId, year, month));

    return report;
}