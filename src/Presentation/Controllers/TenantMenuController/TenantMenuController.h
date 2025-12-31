#ifndef TENANTMENUCONTROLLER_H
#define TENANTMENUCONTROLLER_H

#include <memory>
#include <RentalContract/RentalContract.h>

#include "Domain/User/TenantUser.h"
#include "Controllers/MaintenanceRequestController/MaintenanceRequestController.h"
#include "Application/UseCases/Apartment/Interfaces/IApartmentRepository.h"

using namespace std;

class TenantMenuController {
private:
    shared_ptr<MaintenanceRequestController> maintenanceRequestController;
    shared_ptr<IApartmentRepository> apartmentRepository;

public:
    explicit TenantMenuController(
        shared_ptr<MaintenanceRequestController> maintenanceCtrl,
        shared_ptr<IApartmentRepository> apartmentRepo);

    void execute(shared_ptr<TenantUser> tenant, shared_ptr<RentalContract> contract);

    ~TenantMenuController() = default;
};

#endif // TENANTMENUCONTROLLER_H
