// src/Application/UseCases/Reports/GenerateGlobalBuildingReportUseCase.cpp
#include "GenerateGlobalBuildingReportUseCase.h"
#include "GenerateMonthlyBuildingReportUseCase.h"
#include <stdexcept>

GenerateGlobalBuildingReportUseCase::GenerateGlobalBuildingReportUseCase(
    ExpenseRepository& expenseRepo)
    : expenseRepo_(expenseRepo) {}

GlobalBuildingReport GenerateGlobalBuildingReportUseCase::execute(const std::string& generationDate) {
    GlobalBuildingReport report(generationDate);

    std::vector<int> buildingIds = buildingRepo_.getAllBuildingIds();


    GenerateMonthlyBuildingReportUseCase monthlyUseCase(expenseRepo_);

    for (int buildingId : buildingIds) {
        auto monthlyReport = monthlyUseCase.execute(buildingId, 2025, 12);
        report.addReport(monthlyReport);
    }

    return report;
}