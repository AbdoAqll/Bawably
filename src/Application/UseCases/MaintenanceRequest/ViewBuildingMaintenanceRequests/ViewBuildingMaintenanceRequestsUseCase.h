#ifndef VIEW_MAINTENANCE_REQUESTS_USE_CASE_H
#define VIEW_MAINTENANCE_REQUESTS_USE_CASE_H

#include <memory>


#include "Application/UseCases/MaintenanceRequest/Interfaces/IMaintenanceRequestRepository.h"
#include "UseCases/IUseCase.h"
#include "UseCases/Building/Interfaces/IBuildingRepository.h"

struct ViewMaintenanceRequestsParams {
    int buildingId;
};

class ViewBuildingMaintenanceRequestsUseCase : public IUseCase{
private:
    std::shared_ptr<IMaintenanceRequestRepository> _maintnenceRequestRepo;
    std::shared_ptr<IBuildingRepository> _buildingRepository;
public:
    ViewBuildingMaintenanceRequestsUseCase(shared_ptr<IMaintenanceRequestRepository> rep, shared_ptr<IBuildingRepository> brep);

    any execute(const any& params = {}) override;

};

#endif