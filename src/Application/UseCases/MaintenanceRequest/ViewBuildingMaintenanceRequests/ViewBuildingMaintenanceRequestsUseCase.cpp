#include "ViewBuildingMaintenanceRequestsUseCase.h"

ViewBuildingMaintenanceRequestsUseCase::ViewBuildingMaintenanceRequestsUseCase(shared_ptr<IMaintenanceRequestRepository> rep)
:_maintnenceRequestRepo(rep){
    UseCaseName = "ViewBuildingMaintenanceRequests";
}

any ViewBuildingMaintenanceRequestsUseCase::execute(const any &params) {
    auto args = any_cast<ViewMaintenanceRequestsParams>(params);

    vector<MaintenanceRequest> buildingRequests = _maintnenceRequestRepo->getRequestsOfBuilding(args.buildingId);

    for (MaintenanceRequest &request : buildingRequests)
        std::cout<<request;

    return {};
}


