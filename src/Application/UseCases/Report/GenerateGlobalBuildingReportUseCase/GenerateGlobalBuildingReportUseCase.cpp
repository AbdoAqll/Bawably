// src/Application/UseCases/Reports/GenerateGlobalBuildingReportUseCase.cpp
#include "GenerateGlobalBuildingReportUseCase.h"
#include "../GenerateMonthlyBuildingReportUseCase/GenerateMonthlyBuildingReportUseCase.h"
#include "Domain/Report/Exceptions/ReportGenerationFailedException.h"

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
    string date = "";
    if (params.has_value()) {
        try {
            date = any_cast<string>(params);
        }
        catch (...) {
            // If it's not a string, try const char*
            try {
                date = string(any_cast<const char*>(params));
            }
            catch (...) {
                // Use empty string as default
                date = "";
            }
        }
    }
    GlobalBuildingReport result = execute(date);
    return any(result);
}

GlobalBuildingReport GenerateGlobalBuildingReportUseCase::execute(const std::string& generationDate) {
    GlobalBuildingReport globalReport(generationDate.empty() ? "" : generationDate);

    auto buildings = buildingRepo_->getAll();

    if (buildings.empty()) {
        throw ReportGenerationFailedException("No buildings found in the system");
    }

    GenerateMonthlyBuildingReportUseCase monthlyUseCase(expenseRepo_, apartmentRepo_, contractRepo_, buildingRepo_);

    for (const auto& building : buildings) {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        int year = 1900 + ltm->tm_year;
        int month = 1 + ltm->tm_mon;

        MonthlyBuildingReport monthlyReport = monthlyUseCase.execute(
            building.getId(),
            year,
            month
        );
        globalReport.addReport(monthlyReport);
    }

    return globalReport;
}