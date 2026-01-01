#include "InMemoryMaintenanceRequestRepository.h"


InMemoryMaintenanceRequestRepository::InMemoryMaintenanceRequestRepository() {
    string mr1Des = "The electricity bill has increased significantly this month. Please check the electrical system for any issues or excessive consumption.";
    MaintenanceRequest mr1(getNewId(), 1, 1, mr1Des, 2);
    requests.insert({mr1.getRequestId(), mr1});

    string mr2Des = "There is a water leak under the kitchen sink. A plumber is needed to fix the pipes as soon as possible.";
    MaintenanceRequest mr2(getNewId(), 2, 4, mr2Des, 3);
    requests.insert({mr2.getRequestId(), mr2});

    string mr3Des = "The elevator is making unusual noises and occasionally stops between floors. Please schedule an urgent inspection and repair.";
    MaintenanceRequest mr3(getNewId(), 3, 7, mr3Des, 4);
    requests.insert({mr3.getRequestId(), mr3});

}

int InMemoryMaintenanceRequestRepository::getNewId() {
    return requestId++;
}

bool InMemoryMaintenanceRequestRepository::save(const MaintenanceRequest& maintenance_request) {
    requests[maintenance_request.getRequestId()] = maintenance_request;
    return true;
}

MaintenanceRequest InMemoryMaintenanceRequestRepository::findById(int id) {
    if (requests.find(id) != requests.end()) {
        return requests[id];
    }
    return MaintenanceRequest();
}

bool InMemoryMaintenanceRequestRepository::exists(int id) {
    return requests.find(id) != requests.end();
}

vector<MaintenanceRequest> InMemoryMaintenanceRequestRepository::getRequestsOfBuilding(int buildingId) {
    vector<MaintenanceRequest>buildingRequests;

    MaintenanceRequest temp;
    for (auto& req : requests) {
        temp = req.second;
        if (temp.getBuildingId() == buildingId)
            buildingRequests.push_back(temp);
    }

    return buildingRequests;
}

vector<MaintenanceRequest> InMemoryMaintenanceRequestRepository::getRequestsByApartment(int buildingId, int apartmentId) {
    vector<MaintenanceRequest> apartmentRequests;

    for (auto& req : requests) {
        MaintenanceRequest temp = req.second;
        if (temp.getBuildingId() == buildingId && temp.getApartmentId() == apartmentId)
            apartmentRequests.push_back(temp);
    }

    return apartmentRequests;
}

vector<MaintenanceRequest> InMemoryMaintenanceRequestRepository::getRequestsByTenant(int tenantId) {
    vector<MaintenanceRequest> tenantRequests;

    for (auto& req : requests) {
        MaintenanceRequest temp = req.second;
        if (temp.getTenantId() == tenantId)
            tenantRequests.push_back(temp);
    }

    return tenantRequests;
}