#ifndef CLOSE_MAINTENANCE_REQUEST_USE_CASE_H
#define CLOSE_MAINTENANCE_REQUEST_USE_CASE_H

#include<memory>
#include "Application/UseCases/MaintenanceRequest/Interfaces/IMaintenanceRequestRepository.h"
#include "Domain/MaintenanceRequest/MaintenanceRequest.h"
#include "Domain/MaintenanceRequest/MaintenanceStatus.h"

class CloseMaintenanceRequestUseCase {
private:
    shared_ptr<IMaintenanceRequestRepository> repository;
public:
    CloseMaintenanceRequestUseCase()=default;

    bool execute(int requestId) {
        if (repository->exists(requestId) == false)
            return false;

        MaintenanceRequest request = repository->findById(requestId);
        request.setStatus(MaintenanceStatus::Completed);

        //there should be a helper class to get the current date
        request.setResolvedAt();

        return repository->save(request);
    }
};

#endif