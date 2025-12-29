#include "TenantUser.h"

TenantUser::TenantUser(int userId, const string& username, const string& password,
    int tenantId, int apartmentId, int buildingId)
    : User(userId, username, password, UserRole::TENANT),
    tenantId(tenantId), apartmentId(apartmentId), buildingId(buildingId) {
}

int TenantUser::getTenantId() const {
    return tenantId;
}

int TenantUser::getApartmentId() const {
    return apartmentId;
}

int TenantUser::getBuildingId() const {
    return buildingId;
}
