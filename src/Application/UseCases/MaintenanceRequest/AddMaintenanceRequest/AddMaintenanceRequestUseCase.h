#ifndef ADD_MAINTENANCEREQUEST_USE_CASE_H
#define ADD_MAINTENANCEREQUEST_USE_CASE_H

#include <memory>

#include "Application/UseCases/MaintenanceRequest/Interfaces/IMaintenanceRequestRepository.h"
#include "../../IUseCase.h"

struct AddMaintenanceRequestParams {
    int apartmentId;
    int buildingId;
    int tenantId = -1;
    string description;
};

class AddMaintenanceRequestUseCase : public IUseCase{
private:
    shared_ptr<IMaintenanceRequestRepository> repository;

public:
    AddMaintenanceRequestUseCase(shared_ptr<IMaintenanceRequestRepository> rep);

    any execute(const any& params = {}) override;

};

#endif //ADD_MAINTENANCEREQUEST_USE_CASE_H