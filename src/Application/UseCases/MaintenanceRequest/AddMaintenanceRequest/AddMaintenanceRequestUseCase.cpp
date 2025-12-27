#include "AddMaintenanceRequestUseCase.h"

AddMaintenanceRequestUseCase::AddMaintenanceRequestUseCase(shared_ptr<IMaintenanceRequestRepository> rep):repository(rep) {
    UseCaseName = "AddMaintenanceRequest";
}

any AddMaintenanceRequestUseCase::execute(const any& params) {
    auto args = any_cast<AddMaintenanceRequestParams>(params);

    MaintenanceRequest newRequest(repository->getNewId(), args.buildingId ,args.apartmentId, args.description, args.tenantId);
    repository->save(newRequest);

    return {};
}

