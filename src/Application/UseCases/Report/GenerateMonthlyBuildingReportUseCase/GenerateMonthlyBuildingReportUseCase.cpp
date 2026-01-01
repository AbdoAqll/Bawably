// src/Application/UseCases/Reports/GenerateMonthlyBuildingReportUseCase.cpp
#include "GenerateMonthlyBuildingReportUseCase.h"
#include "Domain/Report/Exceptions/InvalidBuildingIdException.h"
#include "Domain/Shared/InvalidMonthException.h"
#include "Domain/Shared/InvalidYearException.h"
#include "Domain/Building/Exceptions/BuildingNotExistException.h"


GenerateMonthlyBuildingReportUseCase::GenerateMonthlyBuildingReportUseCase(
    shared_ptr<IExpenseRepository> expenseRepo,
    shared_ptr<IApartmentRepository> apartmentRepo,
    shared_ptr<IRentalContractRepository> contractRepo,
    shared_ptr<IBuildingRepository> buildingRepo
)
    : expenseRepo_(expenseRepo),
    apartmentRepo_(apartmentRepo),
    contractRepo_(contractRepo),
    buildingRepo_(buildingRepo) {
    UseCaseName = "GenerateMonthlyBuildingReport";
}

any GenerateMonthlyBuildingReportUseCase::execute(const any& params) {
    auto p = any_cast<GenerateMonthlyReportParams>(params);
    return execute(p.buildingId, p.year, p.month);
}

MonthlyBuildingReport GenerateMonthlyBuildingReportUseCase::execute(int buildingId, int year, int month) {
    if (buildingId < 0) {
        throw InvalidBuildingIdException(buildingId);
    }

    if (month < 1 || month > 12) {
        throw InvalidMonthException(month);
    }

    if (year < 2000 || year > 2100) {
        throw InvalidYearException(year);
    }

    auto building = buildingRepo_->findById(buildingId);

    MonthlyBuildingReport report(buildingId, year, month);

    auto expenses = expenseRepo_->getByBuildingAndMonth(buildingId, year, month);
    double totalExpenses = 0.0;
    for (const auto& e : expenses) {
        totalExpenses += e.getAmount();
    }
    report.setTotalExpenses(totalExpenses);

    auto apartments = apartmentRepo_->getAll(buildingId);
    report.setTotalApartments(apartments.size());

    auto allContracts = contractRepo_->getAll();
    int rentedCount = 0;
    double totalRent = 0.0;

    auto toDateStr = [](int y, int m, int d) {
        std::ostringstream oss;
        oss << std::setw(4) << std::setfill('0') << y << "-" << std::setw(2) << std::setfill('0') << m << "-" << std::setw(2) << std::setfill('0') << d;
        return oss.str();
    };

    std::string monthStart = toDateStr(year, month, 1);
    std::string monthEnd = toDateStr(year, month, 31);

    for (const auto& contract : allContracts) {
        const std::string& start = contract.getStartDate();
        const std::string& end = contract.getEndDate();

        bool overlaps = false;
        if (!start.empty() && start <= monthEnd) {
            if (end.empty() || end >= monthStart) {
                overlaps = true;
            }
        }

        if (!overlaps) continue;

        for (const auto& apt : apartments) {
            if (apt.getId() == contract.getApartmentId()) {
                rentedCount++;
                totalRent += contract.getMonthlyRent();
                break;
            }
        }
    }
    report.setRentedApartments(rentedCount);
    report.setTotalRentIncome(totalRent);

    return report;
}