#ifndef TENANTMENUCONTROLLER_H
#define TENANTMENUCONTROLLER_H

#include <memory>
#include "Domain/User/TenantUser.h"
#include "Controllers/MaintenanceRequestController/MaintenanceRequestController.h"

using namespace std;

class TenantMenuController {
private:
    shared_ptr<MaintenanceRequestController> maintenanceRequestController;

public:
    explicit TenantMenuController(shared_ptr<MaintenanceRequestController> maintenanceCtrl);

    void execute(shared_ptr<TenantUser> tenant);

    ~TenantMenuController() = default;
};

#endif // TENANTMENUCONTROLLER_H
