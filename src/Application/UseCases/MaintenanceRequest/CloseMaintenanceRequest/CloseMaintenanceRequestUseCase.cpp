#include "CloseMaintenanceRequestUseCase.h"


CloseMaintenanceRequestUseCase::CloseMaintenanceRequestUseCase(shared_ptr<IMaintenanceRequestRepository> rep): repository(rep) {
    UseCaseName = "CloseMaintenanceRequest";
}

any CloseMaintenanceRequestUseCase::execute(const any &params) {
    auto args = any_cast<CloseMaintenanceRequestParams>(params);

    if (repository->exists(args.requestId) == false)
        return false;

    MaintenanceRequest request = repository->findById(args.requestId);
    request.setStatus(MaintenanceStatus::Completed);

    //Inside setResolvedAt, it sets the time as <now>
    request.setResolvedAt();

    return repository->save(request);
}


