#ifndef VIEW_MAINTENANCE_REQUESTS_USE_CASE_H
#define VIEW_MAINTENANCE_REQUESTS_USE_CASE_H

#include <memory>
#include <vector>
#include <iostream>

#include "Application/UseCases/MaintenanceRequest/Interfaces/IMaintenanceRequestRepository.h"
#include "Domain/MaintenanceRequest/MaintenanceRequest.h"
#include "UseCases/IUseCase.h"

struct ViewMaintenanceRequestsParams {
    int buildingId;
};

class ViewBuildingMaintenanceRequestsUseCase : public IUseCase{
private:
    std::shared_ptr<IMaintenanceRequestRepository> _maintnenceRequestRepo;
public:
    ViewBuildingMaintenanceRequestsUseCase(shared_ptr<IMaintenanceRequestRepository> rep);

    any execute(const any& params = {}) override;

};

#endif