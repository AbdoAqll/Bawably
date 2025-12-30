#ifndef TENANT_USER_H
#define TENANT_USER_H

#include "User.h"

class TenantUser : public User {
private:
    int tenantId;
    int apartmentId;
    int buildingId;

public:
    TenantUser(int userId, const string& username, const string& password,
        int tenantId, int apartmentId, int buildingId);

    int getTenantId() const;
    int getApartmentId() const;
    int getBuildingId() const;
};

#endif // TENANT_USER_H
