#include "MaintenanceStatus.h"
#include <string>

using namespace std;

class MaintenanceRequest
{
private:
    int requestId;
    int apartmentId;
    int tenantId;
    string description;
    MaintenanceStatus status;
    string createdAt;
    string resolvedAt;

public:
    MaintenanceRequest(int id, int apartmentId, string &description, int tenantId = -1);

    int getRequestId() const;
    int getApartmentId() const;
    int getTenantId() const;
    string getDescription() const;
    MaintenanceStatus getStatus() const;
    string getCreatedAt() const;
    string getResolvedAt() const;

    void setTenantId(int id);
    void setDescription(string &desc);
    void setStatus(MaintenanceStatus newStatus);
    void setResolvedAt(string &date);

    void markInProgress();
    void markResolved(string &date);
};