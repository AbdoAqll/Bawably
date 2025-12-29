#ifndef VIEWAPARTMENTMAINTENANCEREQUESTSUSECASE_H
#define VIEWAPARTMENTMAINTENANCEREQUESTSUSECASE_H

#include "Application/UseCases/IUseCase.h"
#include "Application/UseCases/MaintenanceRequest/Interfaces/IMaintenanceRequestRepository.h"
#include <memory>

using namespace std;

struct ViewApartmentMaintenanceRequestsParams {
    int buildingId;
    int apartmentId;
};

class ViewApartmentMaintenanceRequestsUseCase : public IUseCase {
private:
    shared_ptr<IMaintenanceRequestRepository> maintenanceRequestRepository;

public:
    explicit ViewApartmentMaintenanceRequestsUseCase(shared_ptr<IMaintenanceRequestRepository> repo);
    any execute(const any& params = {}) override;
};

#endif // VIEWAPARTMENTMAINTENANCEREQUESTSUSECASE_H
