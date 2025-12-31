
#ifndef FINALPROJECT_TENANTCONTROLLER_H
#define FINALPROJECT_TENANTCONTROLLER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <UseCases/IUseCase.h>

using namespace std;

class TenantController {
private:
    unordered_map<string, shared_ptr<IUseCase>> useCases;

public:
    explicit TenantController(vector<shared_ptr<IUseCase>>& useCases);
    void displayMenu();
    void createTenant();
    void removeTenant();
    void getAllTenants();
    void execute();
    ~TenantController() = default;
};



#endif //FINALPROJECT_TENANTCONTROLLER_H