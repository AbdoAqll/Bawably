#include "Tenant.h"

Tenant::Tenant(int id, int apartmentId, string &name, string &nationalId, string &phone, string &moveInDate)
{
    tenantId = id;
    apartmentId = apartmentId;
    fullName = name;
    nationalId = nationalId;
    phoneNumber = phone;
    moveInDate = moveInDate;
}

int Tenant::getTenantId() const
{
    return tenantId;
}

int Tenant::getApartmentId() const
{
    return apartmentId;
}

string Tenant::getFullName() const
{
    return fullName;
}

string Tenant::getNationalId() const
{
    return nationalId;
}

string Tenant::getPhoneNumber() const
{
    return phoneNumber;
}

string Tenant::getMoveInDate() const
{
    return moveInDate;
}

string Tenant::getMoveOutDate() const
{
    return moveOutDate;
}

void Tenant::setPhoneNumber(string &phone)
{
    phoneNumber = phone;
}

void Tenant::setMoveOutDate(string &date)
{
    moveOutDate = date;
}

void Tenant::moveToApartment(int newApartmentId)
{
    apartmentId = newApartmentId;
}
