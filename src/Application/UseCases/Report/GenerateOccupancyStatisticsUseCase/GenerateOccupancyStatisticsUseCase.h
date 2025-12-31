// src/Application/UseCases/Report/GenerateOccupancyStatisticsUseCase/GenerateOccupancyStatisticsUseCase.h
#pragma once

#include "../../../UseCases/IUseCase.h"
#include "../../../../Domain/Report/OccupancyStatistics.h"
#include "../../../UseCases/Building/Interfaces/IBuildingRepository.h"
#include "../../../UseCases/Apartment/Interfaces/IApartmentRepository.h"
#include "../../../UseCases/RentalContract/Interfaces/IRentalContractRepository.h"
#include <memory>

using namespace std;

struct GenerateOccupancyStatsParams {
    int year;
    int month;
};

class GenerateOccupancyStatisticsUseCase : public IUseCase {
private:
    shared_ptr<IBuildingRepository> buildingRepo_;
    shared_ptr<IApartmentRepository> apartmentRepo_;
    shared_ptr<IRentalContractRepository> contractRepo_;

public:
    GenerateOccupancyStatisticsUseCase(
        shared_ptr<IBuildingRepository> buildingRepo,
        shared_ptr<IApartmentRepository> apartmentRepo,
        shared_ptr<IRentalContractRepository> contractRepo
    );

    any execute(const any& params = {}) override;
    OccupancyStatistics execute(int year, int month);
    ~GenerateOccupancyStatisticsUseCase() override = default;
};
