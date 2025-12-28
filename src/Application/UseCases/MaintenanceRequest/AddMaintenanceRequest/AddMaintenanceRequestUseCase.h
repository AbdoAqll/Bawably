#ifndef ADD_MAINTENANCEREQUEST_USE_CASE_H
#define ADD_MAINTENANCEREQUEST_USE_CASE_H

#include <memory>

#include "Application/UseCases/MaintenanceRequest/Interfaces/IMaintenanceRequestRepository.h"
#include "../../IUseCase.h"
#include "UseCases/Building/Interfaces/IBuildingRepository.h"
#include "UseCases/Apartment/Interfaces/IApartmentRepository.h"

struct AddMaintenanceRequestParams {
    int buildingId;
    int tenantId = -1;
    int apartmentNumber;
    string description;
};

class AddMaintenanceRequestUseCase : public IUseCase{
private:
    shared_ptr<IMaintenanceRequestRepository> _maintnenceRequestRepo;
    shared_ptr<IApartmentRepository> _apartmentRepo;
    shared_ptr<IBuildingRepository> _buildingRepo;

public:
    AddMaintenanceRequestUseCase(shared_ptr<IMaintenanceRequestRepository> rep,
        shared_ptr<IApartmentRepository> apartmentRepo, shared_ptr<IBuildingRepository> buildingRepo);

    any execute(const any& params = {}) override;

};

#endif //ADD_MAINTENANCEREQUEST_USE_CASE_H