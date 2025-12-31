// src/Application/UseCases/Report/GenerateOccupancyStatisticsUseCase/GenerateOccupancyStatisticsUseCase.cpp
#include "GenerateOccupancyStatisticsUseCase.h"
#include "Domain/Shared/InvalidMonthException.h"
#include "Domain/Shared/InvalidYearException.h"
#include "Domain/Report/Exceptions/ReportGenerationFailedException.h"
#include <sstream>

GenerateOccupancyStatisticsUseCase::GenerateOccupancyStatisticsUseCase(
    shared_ptr<IBuildingRepository> buildingRepo,
    shared_ptr<IApartmentRepository> apartmentRepo,
    shared_ptr<IRentalContractRepository> contractRepo
)
    : buildingRepo_(buildingRepo),
    apartmentRepo_(apartmentRepo),
    contractRepo_(contractRepo) {
    UseCaseName = "GenerateOccupancyStatistics";
}

any GenerateOccupancyStatisticsUseCase::execute(const any& params) {
    auto p = any_cast<GenerateOccupancyStatsParams>(params);
    return execute(p.year, p.month);
}

OccupancyStatistics GenerateOccupancyStatisticsUseCase::execute(int year, int month) {
    // Validate month (1-12)
    if (month < 1 || month > 12) {
        throw InvalidMonthException(month);
    }

    // Validate year
    if (year < 2000 || year > 2100) {
        throw InvalidYearException(year);
    }

    std::ostringstream period;
    period << "Period: " << month << "/" << year;

    OccupancyStatistics statistics(period.str());

    auto buildings = buildingRepo_->getAll();

    if (buildings.empty()) {
        throw ReportGenerationFailedException("No buildings found in the system");
    }

    auto activeContracts = contractRepo_->getActiveContracts();

    for (const auto& building : buildings) {
        int buildingId = building.getId();
        auto apartments = apartmentRepo_->getAll(buildingId);
        int totalApts = apartments.size();

        // Count occupied apartments in this building
        int occupiedCount = 0;
        for (const auto& contract : activeContracts) {
            for (const auto& apt : apartments) {
                if (apt.getId() == contract.getApartmentId()) {
                    occupiedCount++;
                    break;
                }
            }
        }

        statistics.addBuildingData(buildingId, totalApts, occupiedCount);
    }

    return statistics;
}
