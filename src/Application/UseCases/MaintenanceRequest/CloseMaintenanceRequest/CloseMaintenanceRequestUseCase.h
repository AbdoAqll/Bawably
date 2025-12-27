#ifndef CLOSE_MAINTENANCE_REQUEST_USE_CASE_H
#define CLOSE_MAINTENANCE_REQUEST_USE_CASE_H

#include<memory>
#include "Application/UseCases/MaintenanceRequest/Interfaces/IMaintenanceRequestRepository.h"
#include "UseCases/IUseCase.h"

struct CloseMaintenanceRequestParams {
    int requestId;
};

class CloseMaintenanceRequestUseCase: public IUseCase {
private:
    shared_ptr<IMaintenanceRequestRepository> repository;
public:
    CloseMaintenanceRequestUseCase(shared_ptr<IMaintenanceRequestRepository> rep);
    any execute(const any &params) override;
};

#endif