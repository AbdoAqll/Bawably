// src/Application/UseCases/Report/GenerateRevenueStatisticsUseCase/GenerateRevenueStatisticsUseCase.cpp
#include "GenerateRevenueStatisticsUseCase.h"
#include "Domain/Shared/InvalidMonthException.h"
#include "Domain/Shared/InvalidYearException.h"
#include "Domain/Report/Exceptions/ReportGenerationFailedException.h"
#include "Domain/RentPayment/PaymentStatus.h"
#include <sstream>

GenerateRevenueStatisticsUseCase::GenerateRevenueStatisticsUseCase(
    shared_ptr<IBuildingRepository> buildingRepo,
    shared_ptr<IApartmentRepository> apartmentRepo,
    shared_ptr<IRentalContractRepository> contractRepo,
    shared_ptr<IRentPaymentRepository> paymentRepo)
    : buildingRepo_(buildingRepo),
    apartmentRepo_(apartmentRepo),
    contractRepo_(contractRepo),
    paymentRepo_(paymentRepo) {
    UseCaseName = "GenerateRevenueStatistics";
}

any GenerateRevenueStatisticsUseCase::execute(const any& params) {
    auto p = any_cast<GenerateRevenueStatsParams>(params);
    return execute(p.year, p.month);
}

RevenueStatistics GenerateRevenueStatisticsUseCase::execute(int year, int month) {
    // Validate month (1-12)
    if (month < 1 || month > 12) {
        throw InvalidMonthException(month);
    }

    // Validate year
    if (year < 2000 || year > 2100) {
        throw InvalidYearException(year);
    }

    std::ostringstream period;
    period << "Revenue Analysis for " << month << "/" << year;

    RevenueStatistics statistics(period.str());

    auto buildings = buildingRepo_->getAll();

    if (buildings.empty()) {
        throw ReportGenerationFailedException("No buildings found in the system");
    }

    auto activeContracts = contractRepo_->getActiveContracts();

    for (const auto& building : buildings) {
        int buildingId = building.getId();
        auto apartments = apartmentRepo_->getAll(buildingId);

        // Calculate revenue for this building for the specific month/year
        double revenue = 0.0;
        int totalTenants = 0;
        int paidTenants = 0;

        // Get all payments for the specified month/year
        auto monthPayments = paymentRepo_->findByMonth(month, year);

        for (const auto& contract : activeContracts) {
            for (const auto& apt : apartments) {
                if (apt.getId() == contract.getApartmentId()) {
                    totalTenants++;

                    // Check if this tenant paid for this month
                    bool hasPaid = false;
                    for (const auto& payment : monthPayments) {
                        if (payment.getContractId() == contract.getContractId()) {
                            // Add actual amount paid (could be partial or full)
                            revenue += payment.getAmountPaid();
                            if (payment.getStatus() == PaymentStatus::Paid) {
                                paidTenants++;
                            }
                            hasPaid = true;
                            break;
                        }
                    }

                    // If not paid at all, revenue is 0 for this tenant
                    // (already initialized to 0)

                    break;
                }
            }
        }

        statistics.addBuildingData(buildingId, revenue, paidTenants, totalTenants);
    }

    return statistics;
}
