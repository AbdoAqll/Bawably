#ifndef MAINTENANCEREQUEST_REPOSITORY_H
#define MAINTENANCEREQUEST_REPOSITORY_H

#include "Application/UseCases/MaintenanceRequest/Interfaces/IMaintenanceRequestRepository.h"
#include "Domain/MaintenanceRequest/MaintenanceRequest.h"
#include <unordered_map>
#include <vector>

class InMemoryMaintenanceRequestRepository :public IMaintenanceRequestRepository {
private:
    unordered_map<int, MaintenanceRequest> requests;

public:
    InMemoryMaintenanceRequestRepository();
    ~InMemoryMaintenanceRequestRepository() override = default;

    int getNewId() override;
    bool save(const MaintenanceRequest& maintenance_request)override;
    MaintenanceRequest findById(int id) override;
    bool exists(int id) override;
    vector<MaintenanceRequest> getRequestsOfBuilding(int buildingId) override;
    vector<MaintenanceRequest> getRequestsByApartment(int buildingId, int apartmentId) override;
    vector<MaintenanceRequest> getRequestsByTenant(int tenantId) override;
};



#endif //MAINTENANCEREQUEST_REPOSITORY_H