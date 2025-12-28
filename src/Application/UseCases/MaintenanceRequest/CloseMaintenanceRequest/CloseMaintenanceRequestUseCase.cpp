#include "CloseMaintenanceRequestUseCase.h"

#include "Domain/MaintenanceRequest/Exceptions/MaintenanceRequestNotFoundException.h"
#include "Domain/MaintenanceRequest/Exceptions/MaintenanceRequestAlreadyClosedException.h"


CloseMaintenanceRequestUseCase::CloseMaintenanceRequestUseCase(shared_ptr<IMaintenanceRequestRepository> rep)
: _maintnenceRequestRepo(rep) {
    UseCaseName = "CloseMaintenanceRequest";
}

any CloseMaintenanceRequestUseCase::execute(const any &params) {
    auto args = any_cast<CloseMaintenanceRequestParams>(params);

    if (!_maintnenceRequestRepo->exists(args.requestId)) {
        throw MaintenanceRequestNotFoundException(args.requestId);
    }

    MaintenanceRequest request = _maintnenceRequestRepo->findById(args.requestId);

    if (request.getStatus() == MaintenanceStatus::Completed) {
        throw MaintenanceRequestAlreadyClosedException(args.requestId);
    }

    request.setStatus(MaintenanceStatus::Completed);

    //Inside setResolvedAt, it sets the time as <now>
    request.setResolvedAt();

    return _maintnenceRequestRepo->save(request);
}


