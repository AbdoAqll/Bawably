#include "InMemoryMaintenanceRequestRepository.h"


int InMemoryMaintenanceRequestRepository::getNewId() {
    return requestId++;
}

bool InMemoryMaintenanceRequestRepository::save(const MaintenanceRequest &maintenance_request){
    requests[maintenance_request.getRequestId()] = maintenance_request;
    return true;
}

MaintenanceRequest InMemoryMaintenanceRequestRepository::findById(int id){
    if (requests.find(id) != requests.end()) {
        return requests[id];
    }
    return MaintenanceRequest();
}

bool InMemoryMaintenanceRequestRepository::exists(int id){
    return requests.find(id) != requests.end();
}

vector<MaintenanceRequest> InMemoryMaintenanceRequestRepository::getRequestsOfBuilding(int buildingId) {
    vector<MaintenanceRequest>buildingRequests;

    MaintenanceRequest temp;
    for (auto &req: requests) {
        temp = req.second;
        if (temp.getBuildingId() == buildingId)
            buildingRequests.push_back(temp);
    }

    return buildingRequests;
}