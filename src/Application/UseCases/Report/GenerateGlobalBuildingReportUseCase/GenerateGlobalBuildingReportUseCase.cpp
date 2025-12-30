// src/Application/UseCases/Reports/GenerateGlobalBuildingReportUseCase.cpp
#include "GenerateGlobalBuildingReportUseCase.h"
#include "GenerateMonthlyBuildingReportUseCase.h"
#include <stdexcept>

GenerateGlobalBuildingReportUseCase::GenerateGlobalBuildingReportUseCase(
    ExpenseRepository& expenseRepo)
    : expenseRepo_(expenseRepo) {}

GlobalBuildingReport GenerateGlobalBuildingReportUseCase::execute(const std::string& generationDate) {
    GlobalBuildingReport report(generationDate);

    // TODO: جلب كل IDs المباني (من BuildingRepository)
    // std::vector<int> buildingIds = buildingRepo_.getAllBuildingIds();

    // مثال: نعمل لمبنيين للتجربة
    std::vector<int> buildingIds = {1, 2};

    GenerateMonthlyBuildingReportUseCase monthlyUseCase(expenseRepo_);

    for (int buildingId : buildingIds) {
        // مولد التقرير الشهري لكل مبنى (مثال: ديسمبر 2025)
        auto monthlyReport = monthlyUseCase.execute(buildingId, 2025, 12);
        report.addReport(monthlyReport);
    }

    return report;
}