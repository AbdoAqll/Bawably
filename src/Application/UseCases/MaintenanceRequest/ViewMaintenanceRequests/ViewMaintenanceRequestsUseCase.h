#ifndef VIEW_MAINTENANCE_REQUESTS_USE_CASE_H
#define VIEW_MAINTENANCE_REQUESTS_USE_CASE_H

#include <memory>
#include <vector>
#include <iostream>

#include "Application/UseCases/MaintenanceRequest/Interfaces/IMaintenanceRequestRepository.h"
#include "Domain/MaintenanceRequest/MaintenanceRequest.h"

class ViewMaintenanceRequestsUseCase {
private:
    std::shared_ptr<IMaintenanceRequestRepository> repository;
public:
    ViewMaintenanceRequestsUseCase() = default;

    bool execute(int buildingId) {
        vector<MaintenanceRequest> buildingRequests = repository->getRequestsOfBuilding(buildingId);

        for (MaintenanceRequest &request : buildingRequests)
            std::cout<<request;

    }

};

#endif