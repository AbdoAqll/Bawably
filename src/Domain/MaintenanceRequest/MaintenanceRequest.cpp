#include "MaintenanceRequest.h"

#include <iomanip> // For std::put_time
#include <sstream> // For std::ostringstream
#include <ctime>   // For std::time and std::localtime

std::string getCurrentDateString() {
    std::time_t now = std::time(nullptr);
    std::tm* ltm = std::localtime(&now);

    std::ostringstream oss;
    // %Y = Year (2025), %m = Month (12), %d = Day (26)
    oss << std::put_time(ltm, "%Y/%m/%d");
    return oss.str();
}

MaintenanceRequest::MaintenanceRequest(int id, int buildingId, int apartmentId, string &description, int tenantId):resolvedAt("Not Resolved Yet")
{
    this->requestId = id;
    this->buildingId = buildingId;
    this->apartmentId = apartmentId;
    this->description = description;
    this->tenantId = tenantId;
    this->status = MaintenanceStatus::Pending;
    this->createdAt = getCurrentDateString();
}

int MaintenanceRequest::getRequestId() const
{
    return this->requestId;
}

int MaintenanceRequest::getBuildingId() const {
    return this->buildingId;
}

int MaintenanceRequest::getApartmentId() const
{
    return this->apartmentId;
}

int MaintenanceRequest::getTenantId() const
{
    return this->tenantId;
}

string MaintenanceRequest::getDescription() const
{
    return this->description;
}

MaintenanceStatus MaintenanceRequest::getStatus() const
{
    return this->status;
}

string MaintenanceRequest::getStatusString() const {
    MaintenanceStatus currentStatus = this->getStatus();
    if (currentStatus == MaintenanceStatus::InProgress)
        return "InProgress";

    if (currentStatus == MaintenanceStatus::Completed)
        return "Completed";


    return "Pending";
}

string MaintenanceRequest::getCreatedAt() const
{
    return this->createdAt;
}

string MaintenanceRequest::getResolvedAt() const
{
    return this->resolvedAt;
}

void MaintenanceRequest::setTenantId(int id)
{
    this->tenantId = id;
}

void MaintenanceRequest::setDescription(string &desc)
{
    this->description = desc;
}

void MaintenanceRequest::setStatus(MaintenanceStatus newStatus)
{
    this->status = newStatus;
}

void MaintenanceRequest::setResolvedAt()
{
    this->resolvedAt = getCurrentDateString();
}

void MaintenanceRequest::markInProgress()
{
    this->status = MaintenanceStatus::InProgress;
}

void MaintenanceRequest::markResolved(string &date)
{
    this->status = MaintenanceStatus::Completed;
}



ostream &operator<<(ostream &os, MaintenanceRequest &request) {
    os<<"Request id: "<<request.getRequestId()<<endl;
    os<<"Building Id: "<<request.getBuildingId()<<endl;
    os<<"Apartment Id: "<<request.getApartmentId()<<endl;

    if (request.getTenantId() != -1)
        os<<"Request Issued by Tenant with Id: "<<request.getTenantId()<<endl;
    else
        os<<"Request Issued by Property Owner"<<endl;

    os<<"Description: "<<request.getDescription()<<endl;
    os<<"Issued Date: "<<request.getCreatedAt()<<endl;

    string status = request.getStatusString();
    os<<"Status: "<<status<<endl;
    os<<"Resolving Date: "<<request.getResolvedAt()<<endl;
}
