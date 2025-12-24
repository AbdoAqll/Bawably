#include "RentalContract.h"

RentalContract::RentalContract(int id, int apartmentId, int tenantId, double monthlyRent, string &startDate)
{
    contractId = id;
    apartmentId = apartmentId;
    tenantId = tenantId;
    monthlyRent = monthlyRent;
    startDate = startDate;
    isActive = true;
}

int RentalContract::getContractId() const
{
    return contractId;
}

int RentalContract::getApartmentId() const
{
    return apartmentId;
}

int RentalContract::getTenantId() const
{
    return tenantId;
}

double RentalContract::getMonthlyRent() const
{
    return monthlyRent;
}

string RentalContract::getStartDate() const
{
    return startDate;
}

string RentalContract::getEndDate() const
{
    return endDate;
}

bool RentalContract::getIsActive() const
{
    return isActive;
}

void RentalContract::setEndDate(string &newEndDate)
{
    endDate = newEndDate;
}

void RentalContract::terminateContract(string &terminationDate)
{
    isActive = false;
    endDate = terminationDate;
}
