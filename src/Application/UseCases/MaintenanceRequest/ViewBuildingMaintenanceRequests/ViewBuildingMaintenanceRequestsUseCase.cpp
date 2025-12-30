#include "ViewBuildingMaintenanceRequestsUseCase.h"

#include <iostream>

#include "Domain/Building/Exceptions/BuildingNotExistException.h"

ViewBuildingMaintenanceRequestsUseCase::ViewBuildingMaintenanceRequestsUseCase(shared_ptr<IMaintenanceRequestRepository> rep
    , shared_ptr<IBuildingRepository> brep)
:_maintnenceRequestRepo(rep), _buildingRepository(brep){
    UseCaseName = "ViewBuildingMaintenanceRequests";
}

any ViewBuildingMaintenanceRequestsUseCase::execute(const any &params) {
    auto args = any_cast<ViewMaintenanceRequestsParams>(params);

    if (!_buildingRepository->exists(args.buildingId)) {
        throw BuildingNotExistException(args.buildingId);
    }

    vector<MaintenanceRequest> buildingRequests = _maintnenceRequestRepo->getRequestsOfBuilding(args.buildingId);

    for (MaintenanceRequest &request : buildingRequests)
        std::cout<<request;

    return {};
}


