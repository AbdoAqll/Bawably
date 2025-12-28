#ifndef IMAINTENANCEREQUEST_Repository_H
#define IMAINTENANCEREQUEST_Repository_H

#include<vector>
#include "Domain/MaintenanceRequest/MaintenanceRequest.h"


class IMaintenanceRequestRepository {
protected:
    int requestId = 1;
public:
    virtual ~IMaintenanceRequestRepository() = default;

    virtual bool save(const MaintenanceRequest &maintenance_request)=0;
    virtual MaintenanceRequest findById(int id)=0;
    virtual bool exists(int id)=0;
    virtual int getNewId()=0;
    virtual vector<MaintenanceRequest> getRequestsOfBuilding(int buildingId) = 0;
};


#endif //IMAINTENANCEREQUEST_Repository_H