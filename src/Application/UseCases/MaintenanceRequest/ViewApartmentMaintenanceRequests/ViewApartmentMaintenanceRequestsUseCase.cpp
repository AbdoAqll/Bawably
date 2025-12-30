#include "ViewApartmentMaintenanceRequestsUseCase.h"
#include <iostream>

ViewApartmentMaintenanceRequestsUseCase::ViewApartmentMaintenanceRequestsUseCase(
    shared_ptr<IMaintenanceRequestRepository> repo)
    : maintenanceRequestRepository(repo) {
    UseCaseName = "ViewApartmentMaintenanceRequests";
}

any ViewApartmentMaintenanceRequestsUseCase::execute(const any &params) {
    ViewApartmentMaintenanceRequestsParams viewParams = any_cast<ViewApartmentMaintenanceRequestsParams>(params);

    vector<MaintenanceRequest> requests = maintenanceRequestRepository->getRequestsByApartment(
        viewParams.buildingId, viewParams.apartmentId);

    return requests;
}
