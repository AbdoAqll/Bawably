#ifndef MAINTENANCEREQUEST_REPOSITORY_H
#define MAINTENANCEREQUEST_REPOSITORY_H

#include "Application/UseCases/MaintenanceRequest/Interfaces/IMaintenanceRequestRepository.h"
#include "Domain/MaintenanceRequest/MaintenanceRequest.h"
#include <unordered_map>
#include <vector>

class MaintenanceRequestRepository :public IMaintenanceRequestRepository {
private:
    unordered_map<int, MaintenanceRequest> requests;

public:
    MaintenanceRequestRepository()= default;
    ~MaintenanceRequestRepository()= default;

    int getNewId() {
        return requestId++;
    }

    bool save(const MaintenanceRequest &maintenance_request)override {
        requests[maintenance_request.getRequestId()] = maintenance_request;
        return true;
    }

    MaintenanceRequest findById(int id) override {
        if (requests.find(id) != requests.end()) {
            return requests[id];
        }
        return MaintenanceRequest();
    }

    bool exists(int id) override{
        return requests.find(id) != requests.end();
    }

    vector<MaintenanceRequest> getRequestsOfBuilding(int buildingId) {
        vector<MaintenanceRequest>buildingRequests;

        MaintenanceRequest temp;
        for (auto &req: requests) {
            temp = req.second;
            if (temp.getBuildingId() == buildingId)
                buildingRequests.push_back(temp);
        }

        return buildingRequests;
    }

};



#endif //MAINTENANCEREQUEST_REPOSITORY_H