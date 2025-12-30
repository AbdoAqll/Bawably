#ifndef MAINTENANCE_REQUEST_CONTROLLER_H
#define MAINTENANCE_REQUEST_CONTROLLER_H
#include <memory>
#include <unordered_map>
#include <vector>

#include <Application/UseCases/IUseCase.h>

class MaintenanceRequestController {
private:
    std::unordered_map<string, shared_ptr<IUseCase>> useCases;

public:
    explicit MaintenanceRequestController(vector<shared_ptr<IUseCase>>& useCases);
    void displayMenu();
    void createMaintenanceRequest(int buildingId);
    void createMaintenanceRequestForTenant(int buildingId, int apartmentId, int tenantId);
    void getBuildingMaintenanceRequest(int buildingId);
    void getApartmentMaintenanceHistory(int buildingId, int apartmentId);
    void closeMaintenanceRequest();
    void execute(int buildingId);
    void executeForOwner(int buildingId); 
};

#endif