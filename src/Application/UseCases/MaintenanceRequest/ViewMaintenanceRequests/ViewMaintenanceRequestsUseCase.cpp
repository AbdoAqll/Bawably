#include "ViewMaintenanceRequestsUseCase.h"

ViewMaintenanceRequestsUseCase::ViewMaintenanceRequestsUseCase(shared_ptr<IMaintenanceRequestRepository> rep) :repository(rep){
    UseCaseName = "ViewMaintenanceRequests";
}

any ViewMaintenanceRequestsUseCase::execute(const any &params) {
    auto args = any_cast<ViewMaintenanceRequestsParams>(params);

    vector<MaintenanceRequest> buildingRequests = repository->getRequestsOfBuilding(args.buildingId);

    for (MaintenanceRequest &request : buildingRequests)
        std::cout<<request;

    return {};
}


