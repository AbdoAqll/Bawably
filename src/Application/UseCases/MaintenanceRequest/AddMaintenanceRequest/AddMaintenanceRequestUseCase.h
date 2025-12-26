#ifndef ADD_MAINTENANCEREQUEST_USE_CASE_H
#define ADD_MAINTENANCEREQUEST_USE_CASE_H

#include <memory>

#include "Application/UseCases/MaintenanceRequest/Interfaces/IMaintenanceRequestRepository.h"

class AddMaintenanceRequestUseCase {
private:
    shared_ptr<IMaintenanceRequestRepository> repository;

public:
    AddMaintenanceRequestUseCase(shared_ptr<IMaintenanceRequestRepository> rep):repository(rep){}

    //to be implemented
    bool execute(int apartmentId, int buildingId, string description, int tenantId=-1) {
        MaintenanceRequest newRequest(repository->getNewId(), buildingId ,apartmentId, description, tenantId);
        return repository->save(newRequest);
    }
};

#endif //ADD_MAINTENANCEREQUEST_USE_CASE_H