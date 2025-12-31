
#ifndef FINALPROJECT_TENANTCONTROLLER_H
#define FINALPROJECT_TENANTCONTROLLER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "../Application/UseCases/IUseCase.h"

using namespace std;

// class ApartmentController;
// class MaintenanceRequestController;

class TenantController {
    unordered_map<string, shared_ptr<IUseCase>> useCases;
    shared_ptr<TenantController> tenantController;

public:
    TenantController(vector<shared_ptr<IUseCase>>& useCases,
        shared_ptr<TenantController> tenantController);
    void displayMenu();
    void createTenant();
    void removeTenant();
    void getAllTenants();
    void execute();
    ~TenantController() = default;
};



#endif //FINALPROJECT_TENANTCONTROLLER_H