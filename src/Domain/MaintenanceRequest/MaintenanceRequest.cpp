#include "MaintenanceRequest.h"

MaintenanceRequest::MaintenanceRequest(int id, int apartmentId, string &description, int tenantId)
{
}

int MaintenanceRequest::getRequestId() const
{
    return 0;
}

int MaintenanceRequest::getApartmentId() const
{
    return 0;
}

int MaintenanceRequest::getTenantId() const
{
    return 0;
}

string MaintenanceRequest::getDescription() const
{
    return string();
}

MaintenanceStatus MaintenanceRequest::getStatus() const
{
    return MaintenanceStatus();
}

string MaintenanceRequest::getCreatedAt() const
{
    return string();
}

string MaintenanceRequest::getResolvedAt() const
{
    return string();
}

void MaintenanceRequest::setTenantId(int id)
{
}

void MaintenanceRequest::setDescription(string &desc)
{
}

void MaintenanceRequest::setStatus(MaintenanceStatus newStatus)
{
}

void MaintenanceRequest::setResolvedAt(string &date)
{
}

void MaintenanceRequest::markInProgress()
{
}

void MaintenanceRequest::markResolved(string &date)
{
}
