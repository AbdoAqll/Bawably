#ifndef MaintenanceRequest_h
#define MaintenanceRequest_h

#include "MaintenanceStatus.h"
#include <string>

using namespace std;

class MaintenanceRequest
{
private:
    int requestId;
    int buildingId;
    int apartmentId;
    int tenantId;
    string description;
    MaintenanceStatus status;
    string createdAt;
    string resolvedAt;

public:
    MaintenanceRequest(int id, int buildingId, int apartmentId, string &description, int tenantId = -1);
    MaintenanceRequest()=default;


    int getRequestId() const;
    int getBuildingId() const;
    int getApartmentId() const;
    int getTenantId() const;
    string getDescription() const;
    MaintenanceStatus getStatus() const;
    string getStatusString() const;
    string getCreatedAt() const;
    string getResolvedAt() const;

    void setTenantId(int id);
    void setDescription(string &desc);
    void setStatus(MaintenanceStatus newStatus);
    void setResolvedAt();

    void markInProgress();
    void markResolved(string &date);

    friend ostream &operator<<(ostream &os, MaintenanceRequest &request);
};

#endif