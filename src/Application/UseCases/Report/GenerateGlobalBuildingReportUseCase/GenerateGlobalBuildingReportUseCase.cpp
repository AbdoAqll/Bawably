// src/Application/UseCases/Reports/GenerateGlobalBuildingReportUseCase.cpp
#include "GenerateGlobalBuildingReportUseCase.h"
#include "../GenerateMonthlyBuildingReportUseCase/GenerateMonthlyBuildingReportUseCase.h"
#include "Domain/Report/Exceptions/ReportGenerationFailedException.h"
#include <sstream>

GenerateGlobalBuildingReportUseCase::GenerateGlobalBuildingReportUseCase(
    shared_ptr<IExpenseRepository> expenseRepo,
    shared_ptr<IBuildingRepository> buildingRepo,
    shared_ptr<IApartmentRepository> apartmentRepo,
    shared_ptr<IRentalContractRepository> contractRepo) :
    expenseRepo_(expenseRepo),
    buildingRepo_(buildingRepo),
    apartmentRepo_(apartmentRepo),
    contractRepo_(contractRepo) {
    UseCaseName = "GenerateGlobalBuildingReport";
}

any GenerateGlobalBuildingReportUseCase::execute(const any& params) {
    auto p = any_cast<GenerateGlobalReportParams>(params);
    GlobalBuildingReport result = execute(p.year, p.month);
    return any(result);
}

GlobalBuildingReport GenerateGlobalBuildingReportUseCase::execute(int endYear, int endMonth) {
    std::ostringstream dateStream;
    dateStream << "Report up to " << endMonth << "/" << endYear;
    GlobalBuildingReport globalReport(dateStream.str());

    auto buildings = buildingRepo_->getAll();

    if (buildings.empty()) {
        throw ReportGenerationFailedException("No buildings found in the system");
    }

    GenerateMonthlyBuildingReportUseCase monthlyUseCase(expenseRepo_, apartmentRepo_, contractRepo_, buildingRepo_);

    const int startYear = 2000;
    const int startMonth = 1;

    for (const auto& building : buildings) {
        double totalExpensesForBuilding = 0.0;
        double totalRentForBuilding = 0.0;
        int totalApartments = 0;
        int rentedApartments = 0;

        // Loop through all months from start to end
        for (int year = startYear; year <= endYear; year++) {
            int monthStart = (year == startYear) ? startMonth : 1;
            int monthEnd = (year == endYear) ? endMonth : 12;

            for (int month = monthStart; month <= monthEnd; month++) {
                MonthlyBuildingReport monthlyReport = monthlyUseCase.execute(
                    building.getId(),
                    year,
                    month
                );
                totalExpensesForBuilding += monthlyReport.getTotalExpenses();
                totalRentForBuilding += monthlyReport.getTotalRentIncome();
                // Keep the latest apartment counts
                totalApartments = monthlyReport.getTotalApartments();
                rentedApartments = monthlyReport.getRentedApartments();
            }
        }

        // Create a summary report for this building with accumulated data
        MonthlyBuildingReport summaryReport(building.getId(), endYear, endMonth);
        summaryReport.setTotalApartments(totalApartments);
        summaryReport.setRentedApartments(rentedApartments);
        summaryReport.setTotalRentIncome(totalRentForBuilding);
        summaryReport.setTotalExpenses(totalExpensesForBuilding);

        globalReport.addReport(summaryReport);
    }

    return globalReport;
}