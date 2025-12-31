// src/Application/UseCases/Report/GenerateRevenueStatisticsUseCase/GenerateRevenueStatisticsUseCase.h
#pragma once

#include "../../../UseCases/IUseCase.h"
#include "../../../../Domain/Report/RevenueStatistics.h"
#include "../../../UseCases/Building/Interfaces/IBuildingRepository.h"
#include "../../../UseCases/Apartment/Interfaces/IApartmentRepository.h"
#include "../../../UseCases/RentalContract/Interfaces/IRentalContractRepository.h"
#include "../../../UseCases/RentPayment/Interfaces/IRentPaymentRepository.h"
#include <memory>

using namespace std;

struct GenerateRevenueStatsParams {
    int year;
    int month;
};

class GenerateRevenueStatisticsUseCase : public IUseCase {
private:
    shared_ptr<IBuildingRepository> buildingRepo_;
    shared_ptr<IApartmentRepository> apartmentRepo_;
    shared_ptr<IRentalContractRepository> contractRepo_;
    shared_ptr<IRentPaymentRepository> paymentRepo_;

public:
    GenerateRevenueStatisticsUseCase(
        shared_ptr<IBuildingRepository> buildingRepo,
        shared_ptr<IApartmentRepository> apartmentRepo,
        shared_ptr<IRentalContractRepository> contractRepo,
        shared_ptr<IRentPaymentRepository> paymentRepo
    );

    any execute(const any& params = {}) override;
    RevenueStatistics execute(int year, int month);
    ~GenerateRevenueStatisticsUseCase() override = default;
};
